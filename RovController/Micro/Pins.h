/*
 * Pins.h
 *
 * Created: 3/20/2020 3:51:47 PM
 *  Author: zcarey
 */ 


#ifndef PINS_H_
#define PINS_H_

#include <avr/io.h>

//=======================Macros===========================
typedef volatile uint8_t Register;
typedef volatile uint16_t Register16;
#define SetHigh(Port, pin) ((Port) |= (pin))
#define SetLow(Port, pin) ((Port) &= ~(pin))
#define SetOutput(Port, pin) ((Port) |= (pin))
#define SetInput(Port, pin) ((Port) &= ~(pin))

#define bit(b) (1UL << (b))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
//=================COUNTER==================//
#define DDR_OC0A DDRB
#define PORT_OC0A PORTB
#define PIN_OC0A PINA
#define MASK_OC0A _BV(PB7)

#define DDR_OC0B DDRG
#define PORT_OC0B PORTG
#define PIN_OC0B PING
#define MASK_OC0B _BV(PG5)

#define DDR_OC1 DDRB
#define PORT_OC1 PORTB
#define PIN_OC1 PINB
#define MASK_OC1A _BV(PB5)
#define MASK_OC1B _BV(PB6)
#define MASK_OC1C _BV(PB7)

#define DDR_OC2A DDRB
#define PORT_OC2A PORTB
#define PIN_OC2A PINB
#define MASK_OC2A _BV(PB4)

#define DDR_OC2B DDRH
#define PORT_OC2B PORTH
#define PIN_OC2B PINH
#define MASK_OC2B _BV(PH6)

#define DDR_OC3 DDRE
#define PORT_OC3 PORTE
#define PIN_OC3 PINE
#define MASK_OC3A _BV(PE3)
#define MASK_OC3B _BV(PE4)
#define MASK_OC3C _BV(PE5)

#define DDR_OC4 DDRH
#define PORT_OC4 PORTH
#define PIN_OC4 PINH
#define MASK_OC4A _BV(PH3)
#define MASK_OC4B _BV(PH4)
#define MASK_OC4C _BV(PH5)

#define DDR_OC5 DDRL
#define PORT_OC5 PORTL
#define PIN_OC5 PINL
#define MASK_OC5A _BV(PL3)
#define MASK_OC5B _BV(PL4)
#define MASK_OC5C _BV(PL5)

//=================SPI==================//
#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define PIN_SPI PINB
#define MASK_SS _BV(PINB0)
#define MASK_SCK _BV(PINB1)
#define MASK_MOSI _BV(PINB2)
#define MASK_MISO _BV(PINB3)

//=================TWI==================//
#define DDR_TWI DDRD
#define PORT_TWI PORTD
#define PIN_TWI PIND
#define MASK_SCL _BV(PD0)
#define MASK_SDA _BV(PD1)

//=================SERIAL==================//
#define DDR_SERIAL0 DDRE
#define PORT_SERIAL0 PORTE
#define PIN_SERIAL0 PINE
#define MASK_RX0 _BV(PE0)
#define MASK_TX0 _BV(PE1)

#define DDR_SERIAL1 DDRD
#define PORT_SERIAL1 PORTD
#define PIN_SERIAL1 PIND
#define MASK_RX1 _BV(PD2)
#define MASK_TX1 _BV(PD3)

#define DDR_SERIAL2 DDRH
#define PORT_SERIAL2 PORTH
#define PIN_SERIAL2 PINH
#define MASK_RX2 _BV(PH0)
#define MASK_TX2 _BV(PH1)

#define DDR_SERIAL3 DDRJ
#define PORT_SERIAL3 PORTJ
#define PIN_SERIAL3 PINJ
#define MASK_RX3 _BV(PJ0)
#define MASK_TX3 _BV(PJ1)

#endif /* PINS_H_ */