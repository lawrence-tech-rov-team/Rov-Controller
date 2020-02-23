/*
 * Wire.cpp
 *
 * Created: 2/23/2020 11:57:57 AM
 *  Author: zcarey
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "Wire.h"
#include "../../Utils/CpuFreq.h"
#include <util/twi.h>

#define TwiDDR PORTD
#define TwiPort PORTD
#define SDA _BV(PIND1)
#define SCL _BV(PIND0)

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Initialize Class Variables //////////////////////////////////////////////////

uint8_t TwoWire::rxBuffer[TWI_BUFFER_LENGTH];
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;

uint8_t TwoWire::txAddress = 0;
uint8_t TwoWire::txBuffer[TWI_BUFFER_LENGTH];
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;

bool TwoWire::transmitting = false;
void (*TwoWire::user_onRequest)(void);
void (*TwoWire::user_onReceive)(int);

// TWI Variables ////////////////////////////////////////////////////////////////
static volatile uint8_t twi_state;
static volatile uint8_t twi_slarw;
static volatile uint8_t twi_sendStop;			// should the transaction end with a stop
static volatile uint8_t twi_inRepStart;			// in the middle of a repeated start

static void (*twi_onSlaveTransmit)(void);
static void (*twi_onSlaveReceive)(uint8_t*, int);

static uint8_t twi_masterBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_masterBufferIndex;
static volatile uint8_t twi_masterBufferLength;

static uint8_t twi_txBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_txBufferIndex;
static volatile uint8_t twi_txBufferLength;

static uint8_t twi_rxBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_rxBufferIndex;

static volatile uint8_t twi_error;

// Constructors ////////////////////////////////////////////////////////////////

TwoWire::TwoWire()
{
}

// Public Methods //////////////////////////////////////////////////////////////

void TwoWire::begin(void)
{
	rxBufferIndex = 0;
	rxBufferLength = 0;

	txBufferIndex = 0;
	txBufferLength = 0;

	twi_state = TWI_READY;
	twi_sendStop = true;		// default value
	twi_inRepStart = false;
	
	TwiPort |= SDA | SCL; // activate internal pullups for twi.

	// initialize twi prescaler and bit rate
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;

	/* twi bit rate formula from atmega128 manual pg 204
	SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR))
	note: TWBR should be 10 or higher for master mode
	It is 72 for a 16mhz Wiring board with 100kHz TWI */

	// enable twi module, acks, and twi interrupt
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
	
	twi_onSlaveTransmit = onRequestService; // default callback must exist
	twi_onSlaveReceive = onReceiveService; // default callback must exist
}

void TwoWire::begin(uint8_t address)
{
	begin();
	// set twi slave address (skip over TWGCE bit)
	TWAR = address << 1;
}

void TwoWire::begin(int address)
{
	begin((uint8_t)address);
}

void TwoWire::end(void)
{
	// disable twi module, acks, and twi interrupt
	TWCR &= ~(_BV(TWEN) | _BV(TWIE) | _BV(TWEA));

	// deactivate internal pullups for twi.
	TwiPort &= ~(SDA | SCL);
}

void TwoWire::setClock(uint32_t frequency)
{
	TWBR = ((F_CPU / frequency) - 16) / 2;
  
  /* twi bit rate formula from atmega128 manual pg 204
  SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR))
  note: TWBR should be 10 or higher for master mode
  It is 72 for a 16mhz Wiring board with 100kHz TWI */
}

void reply(uint8_t ack)
{
	// transmit master read ready signal, with or without ack
	if(ack){
		TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
		}else{
		TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT);
	}
}

void stop(void)
{
	// send stop condition
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

	// wait for stop condition to be exectued on bus
	// TWINT is not set after a stop condition!
	while(TWCR & _BV(TWSTO)){
		continue;
	}

	// update twi state
	twi_state = TWI_READY;
}

void releaseBus(void)
{
	// release bus
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);

	// update twi state
	twi_state = TWI_READY;
}

uint8_t readFrom(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop)
{
	uint8_t i;

	// ensure data will fit into buffer
	if(TWI_BUFFER_LENGTH < length){
		return 0;
	}

	// wait until twi is ready, become master receiver
	while(TWI_READY != twi_state){
		continue;
	}
	twi_state = TWI_MRX;
	twi_sendStop = sendStop;
	// reset error state (0xFF.. no error occured)
	twi_error = 0xFF;

	// initialize buffer iteration vars
	twi_masterBufferIndex = 0;
	twi_masterBufferLength = length-1;  // This is not intuitive, read on...
	// On receive, the previously configured ACK/NACK setting is transmitted in
	// response to the received byte before the interrupt is signalled.
	// Therefor we must actually set NACK when the _next_ to last byte is
	// received, causing that NACK to be sent in response to receiving the last
	// expected byte of data.

	// build sla+w, slave device address + w bit
	twi_slarw = TW_READ;
	twi_slarw |= address << 1;

	if (true == twi_inRepStart) {
		// if we're in the repeated start state, then we've already sent the start,
		// (@@@ we hope), and the TWI statemachine is just waiting for the address byte.
		// We need to remove ourselves from the repeated start state before we enable interrupts,
		// since the ISR is ASYNC, and we could get confused if we hit the ISR before cleaning
		// up. Also, don't enable the START interrupt. There may be one pending from the
		// repeated start that we sent ourselves, and that would really confuse things.
		twi_inRepStart = false;			// remember, we're dealing with an ASYNC ISR
		do {
			TWDR = twi_slarw;
		} while(TWCR & _BV(TWWC));
		TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);	// enable INTs, but not START
	}
	else
	// send start condition
	TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);

	// wait for read operation to complete
	while(TWI_MRX == twi_state){
		continue;
	}

	if (twi_masterBufferIndex < length)
	length = twi_masterBufferIndex;

	// copy twi buffer to data
	for(i = 0; i < length; ++i){
		data[i] = twi_masterBuffer[i];
	}
	
	return length;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop)
{
	if (isize > 0) {
		// send internal address; this mode allows sending a repeated start to access
		// some devices' internal registers. This function is executed by the hardware
		// TWI module on other processors (for example Due's TWI_IADR and TWI_MMR registers)

		beginTransmission(address);

		// the maximum size of internal address is 3 bytes
		if (isize > 3){
			isize = 3;
		}

		// write internal register address - most significant byte first
		while (isize-- > 0)
		write((uint8_t)(iaddress >> (isize*8)));
		endTransmission(false);
	}

	// clamp to buffer length
	if(quantity > TWI_BUFFER_LENGTH){
		quantity = TWI_BUFFER_LENGTH;
	}
	// perform blocking read into buffer
	uint8_t read = readFrom(address, rxBuffer, quantity, sendStop);
	// set rx buffer iterator vars
	rxBufferIndex = 0;
	rxBufferLength = read;

	return read;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint32_t)0, (uint8_t)0, (uint8_t)sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(uint8_t address)
{
	// indicate that we are transmitting
	transmitting = true;
	// set address of targeted slave
	txAddress = address;
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
}

void TwoWire::beginTransmission(int address)
{
	beginTransmission((uint8_t)address);
}

uint8_t writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
	uint8_t i;

	// ensure data will fit into buffer
	if(TWI_BUFFER_LENGTH < length){
		return 1;
	}

	// wait until twi is ready, become master transmitter
	while(TWI_READY != twi_state){
		continue;
	}
	twi_state = TWI_MTX;
	twi_sendStop = sendStop;
	// reset error state (0xFF.. no error occured)
	twi_error = 0xFF;

	// initialize buffer iteration vars
	twi_masterBufferIndex = 0;
	twi_masterBufferLength = length;
	
	// copy data to twi buffer
	for(i = 0; i < length; ++i){
		twi_masterBuffer[i] = data[i];
	}
	
	// build sla+w, slave device address + w bit
	twi_slarw = TW_WRITE;
	twi_slarw |= address << 1;
	
	// if we're in a repeated start, then we've already sent the START
	// in the ISR. Don't do it again.
	//
	if (true == twi_inRepStart) {
		// if we're in the repeated start state, then we've already sent the start,
		// (@@@ we hope), and the TWI statemachine is just waiting for the address byte.
		// We need to remove ourselves from the repeated start state before we enable interrupts,
		// since the ISR is ASYNC, and we could get confused if we hit the ISR before cleaning
		// up. Also, don't enable the START interrupt. There may be one pending from the
		// repeated start that we sent outselves, and that would really confuse things.
		twi_inRepStart = false;			// remember, we're dealing with an ASYNC ISR
		do {
			TWDR = twi_slarw;
		} while(TWCR & _BV(TWWC));
		TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);	// enable INTs, but not START
	}
	else
	// send start condition
	TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE) | _BV(TWSTA);	// enable INTs

	// wait for write operation to complete
	while(wait && (TWI_MTX == twi_state)){
		continue;
	}
	
	if (twi_error == 0xFF)
	return 0;	// success
	else if (twi_error == TW_MT_SLA_NACK)
	return 2;	// error: address send, nack received
	else if (twi_error == TW_MT_DATA_NACK)
	return 3;	// error: data send, nack received
	else
	return 4;	// other twi error
}

//
//	Originally, 'endTransmission' was an f(void) function.
//	It has been modified to take one parameter indicating
//	whether or not a STOP should be performed on the bus.
//	Calling endTransmission(false) allows a sketch to
//	perform a repeated start.
//
//	WARNING: Nothing in the library keeps track of whether
//	the bus tenure has been properly ended with a STOP. It
//	is very possible to leave the bus in a hung state if
//	no call to endTransmission(true) is made. Some I2C
//	devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
	// transmit buffer (blocking)
	uint8_t ret = writeTo(txAddress, txBuffer, txBufferLength, 1, sendStop);
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
	// indicate that we are done transmitting
	transmitting = false;
	return ret;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
	return endTransmission(true);
}

uint8_t transmit(const uint8_t* data, uint8_t length)
{
	uint8_t i;

	// ensure data will fit into buffer
	if(TWI_BUFFER_LENGTH < (twi_txBufferLength+length)){
		return 1;
	}
	
	// ensure we are currently a slave transmitter
	if(TWI_STX != twi_state){
		return 2;
	}
	
	// set length and copy data into tx buffer
	for(i = 0; i < length; ++i){
		twi_txBuffer[twi_txBufferLength+i] = data[i];
	}
	twi_txBufferLength += length;
	
	return 0;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data)
{
	if(transmitting){
		// in master transmitter mode
		// don't bother if buffer is full
		if(txBufferLength >= TWI_BUFFER_LENGTH){
			//setWriteError();
			return 0;
		}
		// put byte in tx buffer
		txBuffer[txBufferIndex] = data;
		++txBufferIndex;
		// update amount in buffer
		txBufferLength = txBufferIndex;
		}else{
		// in slave send mode
		// reply to master
		transmit(&data, 1);
	}
	return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
	if(transmitting){
		// in master transmitter mode
		for(size_t i = 0; i < quantity; ++i){
			write(data[i]);
		}
		}else{
		// in slave send mode
		// reply to master
		transmit(data, quantity);
	}
	return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void)
{
	return rxBufferLength - rxBufferIndex;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void)
{
	int value = -1;
	
	// get each successive byte on each call
	if(rxBufferIndex < rxBufferLength){
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
	}

	return value;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void)
{
	int value = -1;
	
	if(rxBufferIndex < rxBufferLength){
		value = rxBuffer[rxBufferIndex];
	}

	return value;
}

void TwoWire::flush(void)
{
	// XXX: to be implemented.
}

// behind the scenes function that is called when data is received
void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes)
{
	// don't bother if user hasn't registered a callback
	if(!user_onReceive){
		return;
	}
	// don't bother if rx buffer is in use by a master requestFrom() op
	// i know this drops data, but it allows for slight stupidity
	// meaning, they may not have read all the master requestFrom() data yet
	if(rxBufferIndex < rxBufferLength){
		return;
	}
	// copy twi rx buffer into local read buffer
	// this enables new reads to happen in parallel
	for(uint8_t i = 0; i < numBytes; ++i){
		rxBuffer[i] = inBytes[i];
	}
	// set rx iterator vars
	rxBufferIndex = 0;
	rxBufferLength = numBytes;
	// alert user program
	user_onReceive(numBytes);
}

// behind the scenes function that is called when data is requested
void TwoWire::onRequestService(void)
{
	// don't bother if user hasn't registered a callback
	if(!user_onRequest){
		return;
	}
	// reset tx buffer iterator vars
	// !!! this will kill any pending pre-master sendTo() activity
	txBufferIndex = 0;
	txBufferLength = 0;
	// alert user program
	user_onRequest();
}

// sets function called on slave write
void TwoWire::onReceive( void (*function)(int) )
{
	user_onReceive = function;
}

// sets function called on slave read
void TwoWire::onRequest( void (*function)(void) )
{
	user_onRequest = function;
}

ISR(TWI_vect)
{
	switch(TW_STATUS){
		// All Master
		case TW_START:     // sent start condition
		case TW_REP_START: // sent repeated start condition
		// copy device address and r/w bit to output register and ack
		TWDR = twi_slarw;
		reply(1);
		break;

		// Master Transmitter
		case TW_MT_SLA_ACK:  // slave receiver acked address
		case TW_MT_DATA_ACK: // slave receiver acked data
		// if there is data to send, send it, otherwise stop
		if(twi_masterBufferIndex < twi_masterBufferLength){
			// copy data to output register and ack
			TWDR = twi_masterBuffer[twi_masterBufferIndex++];
			reply(1);
			}else{
			if (twi_sendStop)
			stop();
			else {
				twi_inRepStart = true;	// we're gonna send the START
				// don't enable the interrupt. We'll generate the start, but we
				// avoid handling the interrupt until we're in the next transaction,
				// at the point where we would normally issue the start.
				TWCR = _BV(TWINT) | _BV(TWSTA)| _BV(TWEN) ;
				twi_state = TWI_READY;
			}
		}
		break;
		case TW_MT_SLA_NACK:  // address sent, nack received
		twi_error = TW_MT_SLA_NACK;
		stop();
		break;
		case TW_MT_DATA_NACK: // data sent, nack received
		twi_error = TW_MT_DATA_NACK;
		stop();
		break;
		case TW_MT_ARB_LOST: // lost bus arbitration
		twi_error = TW_MT_ARB_LOST;
		releaseBus();
		break;

		// Master Receiver
		case TW_MR_DATA_ACK: // data received, ack sent
		// put byte into buffer
		twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
		case TW_MR_SLA_ACK:  // address sent, ack received
		// ack if more bytes are expected, otherwise nack
		if(twi_masterBufferIndex < twi_masterBufferLength){
			reply(1);
			}else{
			reply(0);
		}
		break;
		case TW_MR_DATA_NACK: // data received, nack sent
		// put final byte into buffer
		twi_masterBuffer[twi_masterBufferIndex++] = TWDR;
		if (twi_sendStop)
		stop();
		else {
			twi_inRepStart = true;	// we're gonna send the START
			// don't enable the interrupt. We'll generate the start, but we
			// avoid handling the interrupt until we're in the next transaction,
			// at the point where we would normally issue the start.
			TWCR = _BV(TWINT) | _BV(TWSTA)| _BV(TWEN) ;
			twi_state = TWI_READY;
		}
		break;
		case TW_MR_SLA_NACK: // address sent, nack received
		stop();
		break;
		// TW_MR_ARB_LOST handled by TW_MT_ARB_LOST case

		// Slave Receiver
		case TW_SR_SLA_ACK:   // addressed, returned ack
		case TW_SR_GCALL_ACK: // addressed generally, returned ack
		case TW_SR_ARB_LOST_SLA_ACK:   // lost arbitration, returned ack
		case TW_SR_ARB_LOST_GCALL_ACK: // lost arbitration, returned ack
		// enter slave receiver mode
		twi_state = TWI_SRX;
		// indicate that rx buffer can be overwritten and ack
		twi_rxBufferIndex = 0;
		reply(1);
		break;
		case TW_SR_DATA_ACK:       // data received, returned ack
		case TW_SR_GCALL_DATA_ACK: // data received generally, returned ack
		// if there is still room in the rx buffer
		if(twi_rxBufferIndex < TWI_BUFFER_LENGTH){
			// put byte in buffer and ack
			twi_rxBuffer[twi_rxBufferIndex++] = TWDR;
			reply(1);
			}else{
			// otherwise nack
			reply(0);
		}
		break;
		case TW_SR_STOP: // stop or repeated start condition received
		// ack future responses and leave slave receiver state
		releaseBus();
		// put a null char after data if there's room
		if(twi_rxBufferIndex < TWI_BUFFER_LENGTH){
			twi_rxBuffer[twi_rxBufferIndex] = '\0';
		}
		// callback to user defined callback
		twi_onSlaveReceive(twi_rxBuffer, twi_rxBufferIndex);
		// since we submit rx buffer to "wire" library, we can reset it
		twi_rxBufferIndex = 0;
		break;
		case TW_SR_DATA_NACK:       // data received, returned nack
		case TW_SR_GCALL_DATA_NACK: // data received generally, returned nack
		// nack back at master
		reply(0);
		break;
		
		// Slave Transmitter
		case TW_ST_SLA_ACK:          // addressed, returned ack
		case TW_ST_ARB_LOST_SLA_ACK: // arbitration lost, returned ack
		// enter slave transmitter mode
		twi_state = TWI_STX;
		// ready the tx buffer index for iteration
		twi_txBufferIndex = 0;
		// set tx buffer length to be zero, to verify if user changes it
		twi_txBufferLength = 0;
		// request for txBuffer to be filled and length to be set
		// note: user must call twi_transmit(bytes, length) to do this
		twi_onSlaveTransmit();
		// if they didn't change buffer & length, initialize it
		if(0 == twi_txBufferLength){
			twi_txBufferLength = 1;
			twi_txBuffer[0] = 0x00;
		}
		// transmit first byte from buffer, fall
		case TW_ST_DATA_ACK: // byte sent, ack returned
		// copy data to output register
		TWDR = twi_txBuffer[twi_txBufferIndex++];
		// if there is more to send, ack, otherwise nack
		if(twi_txBufferIndex < twi_txBufferLength){
			reply(1);
			}else{
			reply(0);
		}
		break;
		case TW_ST_DATA_NACK: // received nack, we are done
		case TW_ST_LAST_DATA: // received ack, but we are done already!
		// ack future responses
		reply(1);
		// leave slave receiver state
		twi_state = TWI_READY;
		break;

		// All
		case TW_NO_INFO:   // no state information
		break;
		case TW_BUS_ERROR: // bus error, illegal stop/start
		twi_error = TW_BUS_ERROR;
		stop();
		break;
	}
}

// Preinstantiate Objects //////////////////////////////////////////////////////

TwoWire Wire = TwoWire();