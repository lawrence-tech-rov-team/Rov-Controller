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


extern HardwarePcbServo ServoA1;
extern HardwarePcbServo ServoA2;
extern HardwarePcbServo ServoA3;
extern HardwarePcbServo ServoA4;
extern HardwarePcbServo ServoA5;

extern HardwarePcbServo ServoB1;
extern HardwarePcbServo ServoB2;
extern HardwarePcbServo ServoB3;
extern HardwarePcbServo ServoB4;
extern HardwarePcbServo ServoB5;
extern HardwarePcbServo ServoB6;

extern TwiServoController PcaServoController;

extern TwiPcbServo ServoC1;
extern TwiPcbServo ServoC2;
extern TwiPcbServo ServoC3;
extern TwiPcbServo ServoC4;
extern TwiPcbServo ServoC5;
extern TwiPcbServo ServoC6;
extern TwiPcbServo ServoC7;
extern TwiPcbServo ServoC8;

extern TwiPcbServo ServoD1;
extern TwiPcbServo ServoD2;
extern TwiPcbServo ServoD3;
extern TwiPcbServo ServoD4;
extern TwiPcbServo ServoD5;
extern TwiPcbServo ServoD6;
extern TwiPcbServo ServoD7;
extern TwiPcbServo ServoD8;

#endif /* PCBPINS_H_ */