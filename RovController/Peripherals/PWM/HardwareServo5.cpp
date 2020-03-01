/*
 * HardwareServo5.cpp
 *
 * Created: 2/29/2020 9:09:47 PM
 *  Author: zcarey
 */ 


#include "HardwareServo.h"

HardwareServo Servo5(ICR5, TCCR5A, TCCR5B, OCR5A, OCR5B, OCR5C);
