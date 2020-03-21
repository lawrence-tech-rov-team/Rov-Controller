/*
 * PcbPins.cpp
 *
 * Created: 3/20/2020 7:16:01 PM
 *  Author: zcarey
 */ 

#include "PcbPins.h"

HardwarePcbServo ServoA1(Servo5, HardwarePcbServo::ServoC);
HardwarePcbServo ServoA2(Servo3, HardwarePcbServo::ServoB);
HardwarePcbServo ServoA3(Servo3, HardwarePcbServo::ServoA);
HardwarePcbServo ServoA4(Servo4, HardwarePcbServo::ServoB);
HardwarePcbServo ServoA5(Servo4, HardwarePcbServo::ServoC);

HardwarePcbServo ServoB1(Servo5, HardwarePcbServo::ServoA);
HardwarePcbServo ServoB2(Servo5, HardwarePcbServo::ServoB);
HardwarePcbServo ServoB3(Servo3, HardwarePcbServo::ServoC);
HardwarePcbServo ServoB4(Servo4, HardwarePcbServo::ServoA);
HardwarePcbServo ServoB5(Servo1, HardwarePcbServo::ServoA);
HardwarePcbServo ServoB6(Servo1, HardwarePcbServo::ServoB);

TwiServoController PcaServoController(0x43); //0x70);

TwiPcbServo ServoC1(PcaServoController, 0);
TwiPcbServo ServoC2(PcaServoController, 2);
TwiPcbServo ServoC3(PcaServoController, 7);
TwiPcbServo ServoC4(PcaServoController, 5);
TwiPcbServo ServoC5(PcaServoController, 8);
TwiPcbServo ServoC6(PcaServoController, 10);
TwiPcbServo ServoC7(PcaServoController, 12);
TwiPcbServo ServoC8(PcaServoController, 14);

TwiPcbServo ServoD1(PcaServoController, 1);
TwiPcbServo ServoD2(PcaServoController, 3);
TwiPcbServo ServoD3(PcaServoController, 6);
TwiPcbServo ServoD4(PcaServoController, 4);
TwiPcbServo ServoD5(PcaServoController, 9);
TwiPcbServo ServoD6(PcaServoController, 11);
TwiPcbServo ServoD7(PcaServoController, 13);
TwiPcbServo ServoD8(PcaServoController, 15);