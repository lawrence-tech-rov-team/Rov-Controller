/*
THIS FILE SHOULD NOT BE INCLUDED DIRECTLY. INSTEAD INCLUDE "PCBPins.h" AND UNCOMMENT THE CORRECT HARDWARE NEEDED.

 * PCB_V1.h
 *
 * Created: 3/5/2020 10:53:30 AM
 *  Author: zcarey
 */ 


#ifndef PCB_V1_H_
#define PCB_V1_H_

#include <avr/io.h>

#define DDR_ENC DDRB
#define PORT_ENC PORTB
#define PIN_ENC PINB
#define MASK_ENC_CS _BV(PB0)

#define DDR_BTN0 DDRF
#define PORT_BTN0 PORTF
#define PIN_BTN0 PORTF
#define MASK_BTN0 _BV(PF1)

#define Servo_A1_setMin Servo5.setMinC
#define Servo_A1_setMax Servo5.setMaxC
#define Servo_A1_enable Servo5.EnableC
#define Servo_A1_setPulse Servo5.setPulseC

#define Servo_A2_setMin Servo5.setMinA
#define Servo_A2_setMax Servo5.setMaxA
#define Servo_A2_enable Servo5.EnableA
#define Servo_A2_setPulse Servo5.setPulseA

#define Servo_A3_setMin Servo5.setMinB
#define Servo_A3_setMax Servo5.setMaxB
#define Servo_A3_enable Servo5.EnableB
#define Servo_A3_setPulse Servo5.setPulseB

#define Servo_A4_setMin Servo3.setMinB
#define Servo_A4_setMax Servo3.setMaxB
#define Servo_A4_enable Servo3.EnableB
#define Servo_A4_setPulse Servo3.setPulseB

#define Servo_A5_setMin Servo3.setMinC
#define Servo_A5_setMax Servo3.setMaxC
#define Servo_A5_enable Servo3.EnableC
#define Servo_A5_setPulse Servo3.setPulseC

//#define Servo_A6_setMin

#define Servo_A7_setMin Servo3.setMinA
#define Servo_A7_setMax Servo3.setMaxA
#define Servo_A7_enable Servo3.EnableA
#define Servo_A7_setPulse Servo3.setPulseC

#define Servo_A8_setMin Servo4.setMinA
#define Servo_A8_setMax Servo4.setMaxA
#define Servo_A8_enable Servo4.EnableA
#define Servo_A8_setPulse Servo4.setPulseA

#define Servo_A9_setMin Servo4.setMinB
#define Servo_A9_setMax Servo4.setMaxB
#define Servo_A9_enable Servo4.EnableB
#define Servo_A9_setPulse Servo4.setPulseB

#define Servo_A10_setMin Servo4.setMinC
#define Servo_A10_setMax Servo4.setMaxC
#define Servo_A10_enable Servo4.EnableC
#define Servo_A10_setPulse Servo4.setPulseC

//#define Servo_A11_setMin 

//#define Servo_A12_setMin

#define Servo_A13_setMin Servo1.setMinA
#define Servo_A13_setMax Servo1.setMaxA
#define Servo_A13_enable Servo1.EnableA
#define Servo_A13_setPulse Servo1.setPulseA

#define Servo_A14_setMin Servo1.setMinB
#define Servo_A14_setMax Servo1.setMaxB
#define Servo_A14_enable Servo1.EnableB
#define Servo_A14_setPulse Servo1.setPulseB

#endif /* PCB_V1_H_ */