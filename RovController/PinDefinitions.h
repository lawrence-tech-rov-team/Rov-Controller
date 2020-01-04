/*
 * PinDefinitions.h
 *
 * Created: 12/25/2019 11:53:14 AM
 *  Author: zcarey
 */ 


#ifndef PINDEFINITIONS_H_
#define PINDEFINITIONS_H_

#include <avr/io.h>

#define SpiPort		PORTB
#define SpiDDR		DDRB
#define SpiPin		PINB
#define SpiPin_SS	_BV(PINB0)
#define SpiPin_SCK	_BV(PINB1)
#define SpiPin_MOSI	_BV(PINB2)
#define SpiPin_MISO	_BV(PINB3)

#define EthernetPort	PORTH
#define EthernetDDR		DDRH
#define EthernetPin		PINH
#define EthernetPin_CS	_BV(PINH5)

typedef volatile uint8_t Register;
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


#endif /* PINDEFINITIONS_H_ */