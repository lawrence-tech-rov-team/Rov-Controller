/*
THIS FILE SHOULD NOT BE INCLUDED DIRECTLY. INSTEAD INCLUDE "PCBPins.h" AND UNCOMMENT THE CORRECT HARDWARE NEEDED.

 * PCB_V3.h
 *
 * Created: 3/5/2020 10:53:41 AM
 *  Author: zcarey
 */ 


#ifndef PCB_V3_H_
#define PCB_V3_H_

#include <avr/io.h>
#include "PcbServo.h"

#define DDR_ENC DDRK
#define PORT_ENC PORTK
#define PIN_ENC PINK
#define MASK_ENC_CS _BV(PK0)

#define DDR_BTN0 DDRF
#define PORT_BTN0 PORTF
#define PIN_BTN0 PORTF
#define MASK_BTN0 _BV(PF0)

#define DDR_BTN1 DDRF
#define PORT_BTN1 PORTF
#define PIN_BTN1 PORTF
#define MASK_BTN1 _BV(PF1)

#define DDR_MISCA DDRA
#define PORT_MISCA PORTA
#define PIN_MISCA PORTA
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

//==============================================

//#define Servo_A1_setMin Servo5.setMinC
//#define Servo_A1_setMax Servo5.setMaxC
//#define Servo_A1_enable Servo5.EnableC
//#define Servo_A1_disable Servo5.DisableC
//#define Servo_A1_setPulse Servo5.setPulseC
extern PcbServo ServoA1;

//#define Servo_A2_setMin Servo3.setMinB
//#define Servo_A2_setMax Servo3.setMaxB
//#define Servo_A2_enable Servo3.EnableB
//#define Servo_A2_disable Servo3.DisableB
//#define Servo_A2_setPulse Servo3.setPulseB
extern PcbServo ServoA2;

//#define Servo_A3_setMin Servo3.setMinA
//#define Servo_A3_setMax Servo3.setMaxA
//#define Servo_A3_enable Servo3.EnableA
//#define Servo_A3_disable Servo3.DisableA
//#define Servo_A3_setPulse Servo3.setPulseA
extern PcbServo ServoA3;

//#define Servo_A4_setMin Servo4.setMinB
//#define Servo_A4_setMax Servo4.setMaxB
//#define Servo_A4_enable Servo4.EnableB
//#define Servo_A4_disable Servo4.DisableB
//#define Servo_A4_setPulse Servo4.setPulseB
extern PcbServo ServoA4;

//#define Servo_A5_setMin Servo4.setMinC
//#define Servo_A5_setMax Servo4.setMaxC
//#define Servo_A5_enable Servo4.EnableC
//#define Servo_A5_disable Servo4.DisableC
//#define Servo_A5_setPulse Servo4.setPulseC
extern PcbServo ServoA5;

//==========================================================

//#define Servo_B1_setMin Servo5.setMinA
//#define Servo_B1_setMax Servo5.setMaxA
//#define Servo_B1_enable Servo5.EnableA
//#define Servo_B1_disable Servo5.DisableA
//#define Servo_B1_setPulse Servo5.setPulseA
extern PcbServo ServoB1;

//#define Servo_B2_setMin Servo5.setMinB
//#define Servo_B2_setMax Servo5.setMaxB
//#define Servo_B2_enable Servo5.EnableB
//#define Servo_B2_disable Servo5.DisableB
//#define Servo_B2_setPulse Servo5.setPulseB
extern PcbServo ServoB2;

//#define Servo_B3_setMin Servo3.setMinC
//#define Servo_B3_setMax Servo3.setMaxC
//#define Servo_B3_enable Servo3.EnableC
//#define Servo_B3_disable Servo3.DisableC
//#define Servo_B3_setPulse Servo3.setPulseC
extern PcbServo ServoB3;

//#define Servo_B4_setMin Servo4.setMinA
//#define Servo_B4_setMax Servo4.setMaxA
//#define Servo_B4_enable Servo4.EnableA
//#define Servo_B4_disable Servo4.DisableA
//#define Servo_B4_setPulse Servo4.setPulseA
extern PcbServo ServoB4;

//#define Servo_B5_setMin Servo1.setMinA
//#define Servo_B5_setMax Servo1.setMaxA
//#define Servo_B5_enable Servo1.EnableA
//#define Servo_B5_disable Servo1.DisableA
//#define Servo_B5_setPulse Servo1.setPulseA
extern PcbServo ServoB5;

//#define Servo_B6_setMin Servo1.setMinB
//#define Servo_B6_setMax Servo1.setMaxB
//#define Servo_B6_enable Servo1.EnableB
//#define Servo_B6_disable Servo1.DisableB
//#define Servo_B6_setPulse Servo1.setPulseB
extern PcbServo ServoB6;

#endif /* PCB_V3_H_ */