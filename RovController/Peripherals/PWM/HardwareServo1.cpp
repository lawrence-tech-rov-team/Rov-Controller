/*
 * HardwareServo1.cpp
 *
 * Created: 2/29/2020 8:09:46 PM
 *  Author: zcarey
 */ 

#include "HardwareServo.h"

HardwareServo Servo1(ICR1, TCCR1A, TCCR1B, OCR1A, OCR1B, OCR1C);