/*
 * PinDefinitions.h
 *
 * Created: 12/25/2019 11:53:14 AM
 *  Author: zcarey
 */ 


#ifndef PINDEFINITIONS_H_
#define PINDEFINITIONS_H_

#include <avr/io.h>
/*
#define SpiPort		PORTB
#define SpiDDR		DDRB
#define SpiPin		PINB
#define SpiPin_SS	_BV(PINB0)
#define SpiPin_SCK	_BV(PINB1)
#define SpiPin_MOSI	_BV(PINB2)
#define SpiPin_MISO	_BV(PINB3)
*/
#define TwiPort		PORTD
#define TwiDDR		DDRD
#define TwiPin		PIND
#define TwiPin_SDA	_BV(PIND1)
#define TwiPin_SCL	_BV(PIND0)

#define EthernetPort	PORTB
#define EthernetDDR		DDRB
#define EthernetPin		PINB
#define EthernetPin_CS	_BV(PINB0)

#define LedPort		PORTB
#define LedDDR		DDRB
#define LedPinPort	PINB
#define LedPin		_BV(PINB7)

#define TestBtnPort		PORTF
#define TestBtnDDR		DDRF
#define TestBtnPinPort	PINF
#define TestBtnPin		_BV(PINF1)


//==================Macros==================
typedef volatile uint8_t Register;
typedef volatile uint16_t Register16;
#define SetHigh(Port, pin) ((Port) |= (pin))
#define SetLow(Port, pin) ((Port) &= ~(pin))
#define SetOutput(Port, pin) ((Port) |= (pin))
#define SetInput(Port, pin) ((Port) &= ~(pin))

//TODO Arduino Definitions
#define bit(b) (1UL << (b))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef volatile uint8_t Register;

#endif /* PINDEFINITIONS_H_ */