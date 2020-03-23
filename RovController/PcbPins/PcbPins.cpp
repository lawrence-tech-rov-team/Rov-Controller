/*
 * PcbPins.cpp
 *
 * Created: 3/20/2020 7:16:01 PM
 *  Author: zcarey
 */ 

#include "PcbPins.h"

HardwarePcbServo PcbServoA1(Servo5, HardwarePcbServo::ServoC);
HardwarePcbServo PcbServoA2(Servo3, HardwarePcbServo::ServoB);
HardwarePcbServo PcbServoA3(Servo3, HardwarePcbServo::ServoA);
HardwarePcbServo PcbServoA4(Servo4, HardwarePcbServo::ServoB);
HardwarePcbServo PcbServoA5(Servo4, HardwarePcbServo::ServoC);

HardwarePcbServo PcbServoB1(Servo5, HardwarePcbServo::ServoA);
HardwarePcbServo PcbServoB2(Servo5, HardwarePcbServo::ServoB);
HardwarePcbServo PcbServoB3(Servo3, HardwarePcbServo::ServoC);
HardwarePcbServo PcbServoB4(Servo4, HardwarePcbServo::ServoA);
HardwarePcbServo PcbServoB5(Servo1, HardwarePcbServo::ServoA);
HardwarePcbServo PcbServoB6(Servo1, HardwarePcbServo::ServoB);

TwiServoController PcaServoController(0x43); //0x70);

TwiPcbServo PcbServoC1(PcaServoController, 0);
TwiPcbServo PcbServoC2(PcaServoController, 2);
TwiPcbServo PcbServoC3(PcaServoController, 7);
TwiPcbServo PcbServoC4(PcaServoController, 5);
TwiPcbServo PcbServoC5(PcaServoController, 8);
TwiPcbServo PcbServoC6(PcaServoController, 10);
TwiPcbServo PcbServoC7(PcaServoController, 12);
TwiPcbServo PcbServoC8(PcaServoController, 14);

TwiPcbServo PcbServoD1(PcaServoController, 1);
TwiPcbServo PcbServoD2(PcaServoController, 3);
TwiPcbServo PcbServoD3(PcaServoController, 6);
TwiPcbServo PcbServoD4(PcaServoController, 4);
TwiPcbServo PcbServoD5(PcaServoController, 9);
TwiPcbServo PcbServoD6(PcaServoController, 11);
TwiPcbServo PcbServoD7(PcaServoController, 13);
TwiPcbServo PcbServoD8(PcaServoController, 15);