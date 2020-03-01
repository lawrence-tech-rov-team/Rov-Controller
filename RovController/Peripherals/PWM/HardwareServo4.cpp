/*
 * HardwareServo4.cpp
 *
 * Created: 2/29/2020 9:09:17 PM
 *  Author: zcarey
 */ 

#include "HardwareServo.h"

HardwareServo Servo4(ICR4, TCCR4A, TCCR4B, OCR4A, OCR4B, OCR4C);
