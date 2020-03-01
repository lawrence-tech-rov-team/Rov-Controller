/*
 * HardwareServo3.cpp
 *
 * Created: 2/29/2020 9:05:56 PM
 *  Author: zcarey
 */ 

#include "HardwareServo.h"

HardwareServo Servo3(ICR3, TCCR3A, TCCR3B, OCR3A, OCR3B, OCR3C);