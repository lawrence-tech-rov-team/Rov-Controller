/*
 * PcbPins.h
 *
 * Created: 3/20/2020 7:15:51 PM
 *  Author: zcarey
 */ 


#ifndef PCBPINS_H_
#define PCBPINS_H_

#include "../Micro/Pins.h"
#include "HardwarePcbServo.h"
#include "TwiPcbServo.h"

#define DDR_ENC DDRK
#define PORT_ENC PORTK
#define PIN_ENC PINK
#define MASK_ENC_CS _BV(PK0)

#define DDR_BTN0 DDRF
#define PORT_BTN0 PORTF
#define PIN_BTN0 PINF
#define MASK_BTN0 _BV(PF0)

#define DDR_BTN1 DDRF
#define PORT_BTN1 PORTF
#define PIN_BTN1 PINF
#define MASK_BTN1 _BV(PF1)

#define DDR_MISCA DDRA
#define PORT_MISCA PORTA
#define PIN_MISCA PINA
#define MASK_MISCA24 _BV(PA2)
#define MASK_MISCA26 _BV(PA4)
#define MASK_MISCA28 _BV(PA6)

#define DDR_MISCB DDRC
#define PORT_MISCB PORTC
#define PIN_MISCB PINC
#define MASK_MISCB30 _BV(PC7)
#define MASK_MISCB32 _BV(PC5)
#define MASK_MISCB34 _BV(PC3)

#define DDR_LED DDRB
#define PORT_LED PORTB
#define MASK_LED _BV(PB7)


extern HardwarePcbServo PcbServoA1;
extern HardwarePcbServo PcbServoA2;
extern HardwarePcbServo PcbServoA3;
extern HardwarePcbServo PcbServoA4;
extern HardwarePcbServo PcbServoA5;

extern HardwarePcbServo PcbServoB1;
extern HardwarePcbServo PcbServoB2;
extern HardwarePcbServo PcbServoB3;
extern HardwarePcbServo PcbServoB4;
extern HardwarePcbServo PcbServoB5;
extern HardwarePcbServo PcbServoB6;

extern TwiServoController PcaServoController;

extern TwiPcbServo PcbServoC1;
extern TwiPcbServo PcbServoC2;
extern TwiPcbServo PcbServoC3;
extern TwiPcbServo PcbServoC4;
extern TwiPcbServo PcbServoC5;
extern TwiPcbServo PcbServoC6;
extern TwiPcbServo PcbServoC7;
extern TwiPcbServo PcbServoC8;

extern TwiPcbServo PcbServoD1;
extern TwiPcbServo PcbServoD2;
extern TwiPcbServo PcbServoD3;
extern TwiPcbServo PcbServoD4;
extern TwiPcbServo PcbServoD5;
extern TwiPcbServo PcbServoD6;
extern TwiPcbServo PcbServoD7;
extern TwiPcbServo PcbServoD8;

#endif /* PCBPINS_H_ */