/*
 * HardwareServo.cpp
 *
 * Created: 2/29/2020 11:14:52 AM
 *  Author: zcarey
 */ 

#include "HardwareServo.h"

#include "../../Utils/CpuFreq.h"
#define CPU_CONST (F_CPU / 8000000)

#define CLK_DISABLE (0)
#define CLK_DIV_1 (_BV(CS00))
#define CLK_DIV_8 (_BV(CS01))
#define CLK_DIV_64 (_BV(CS01) | _BV(CS00))
#define CLK_DIV_256 (_BV(CS02))
#define CLK_DIV_1024 (_B(CS02) | _BV(CS00))

HardwareServo::HardwareServo(Register16 &icr, Register &tccrA, Register &tccrB, Register16 &ocrA, Register16 &ocrB, Register16 &ocrC)
 : _icr(&icr), _tccrA(&tccrA), _tccrB(&tccrB), _ocrA(&ocrA), _ocrB(&ocrB), _ocrC(&ocrC),
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
}

void HardwareServo::EnableB(){
	*_tccrA |= _BV(COM1B1);
}

void HardwareServo::EnableC(){
	*_tccrA |= _BV(COM1C1);
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
