/*
 * HardwareServo.cpp
 *
 * Created: 2/29/2020 11:14:52 AM
 *  Author: zcarey
 */ 

#include "HardwareServo.h"

#include "../Utils/CpuFreq.h"
#define CPU_CONST (F_CPU / 8000000)

#define CLK_DISABLE (0)
#define CLK_DIV_1 (_BV(CS00))
#define CLK_DIV_8 (_BV(CS01))
#define CLK_DIV_64 (_BV(CS01) | _BV(CS00))
#define CLK_DIV_256 (_BV(CS02))
#define CLK_DIV_1024 (_B(CS02) | _BV(CS00))

HardwareServo::HardwareServo(Register16 &icr, Register &tccrA, Register &tccrB, Register16 &ocrA, Register16 &ocrB, Register16 &ocrC, Register &ddr, const uint8_t pinA, const uint8_t pinB, const uint8_t pinC)
 : _icr(&icr), _tccrA(&tccrA), _tccrB(&tccrB), _ocrA(&ocrA), _ocrB(&ocrB), _ocrC(&ocrC),
  _DDR(&ddr), _PINA(pinA), _PINB(pinB), _PINC(pinC),
  _minA(1000), _minB(1000), _minC(1000), _maxA(2000), _maxB(2000), _maxC(2000)
{
	
}

void HardwareServo::begin(){
	*_tccrA = _BV(WGM11); //Fast PWM, ICR top
	*_tccrB = _BV(WGM13) | _BV(WGM12) | CLK_DIV_8; //Clock division and fast PWM
	*_icr = 40000; //Set period to 20ms
}

void HardwareServo::EnableA(){
	*_tccrA |= _BV(COM1A1);
	*_DDR |= _PINA;
}

void HardwareServo::EnableB(){
	*_tccrA |= _BV(COM1B1);
	*_DDR |= _PINB;
}

void HardwareServo::EnableC(){
	*_tccrA |= _BV(COM1C1);
	*_DDR |= _PINC;
}

void HardwareServo::DisableA(){
	*_tccrA &= ~_BV(COM1A1);
}

void HardwareServo::DisableB(){
	*_tccrA &= ~_BV(COM1B1);
}

void HardwareServo::DisableC(){
	*_tccrA &= ~_BV(COM1C1);	
}

void HardwareServo::setPulseA(uint8_t pulse){
	*_ocrA = (uint16_t)((((uint32_t)pulse * (_maxA - _minA)) / 255 + _minA) * CPU_CONST);
}

void HardwareServo::setPulseB(uint8_t pulse){
	*_ocrB = (uint16_t)((((uint32_t)pulse * (_maxB - _minB)) / 255 + _minB) * CPU_CONST);	
}

void HardwareServo::setPulseC(uint8_t pulse){
	*_ocrC = (uint16_t)((((uint32_t)pulse * (_maxC - _minC)) / 255 + _minC) * CPU_CONST);	
}

void HardwareServo::setMinA(uint16_t us){
	_minA = us;
}

void HardwareServo::setMinB(uint16_t us){
	_minB = us;
}

void HardwareServo::setMinC(uint16_t us){
	_minC = us;
}

void HardwareServo::setMaxA(uint16_t us){
	_maxA = us;
}

void HardwareServo::setMaxB(uint16_t us){
	_maxB = us;
}

void HardwareServo::setMaxC(uint16_t us){
	_maxC = us;
}

HardwareServo Servo1(ICR1, TCCR1A, TCCR1B, OCR1A, OCR1B, OCR1C, DDRB, _BV(PINB5), _BV(PINB6), _BV(PINB7));
HardwareServo Servo3(ICR3, TCCR3A, TCCR3B, OCR3A, OCR3B, OCR3C, DDRE, _BV(PINE3), _BV(PINE4), _BV(PINE5));
HardwareServo Servo4(ICR4, TCCR4A, TCCR4B, OCR4A, OCR4B, OCR4C, DDRH, _BV(PINH3), _BV(PINH4), _BV(PINH5));
HardwareServo Servo5(ICR5, TCCR5A, TCCR5B, OCR5A, OCR5B, OCR5C, DDRL, _BV(PINL3), _BV(PINL4), _BV(PINL5));

