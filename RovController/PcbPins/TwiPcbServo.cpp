/*
 * TwiPcbServo.cpp
 *
 * Created: 3/21/2020 12:15:20 AM
 *  Author: zcarey
 */ 

#include "TwiPcbServo.h"

TwiPcbServo::TwiPcbServo(TwiServoController &controller, uint8_t servo)
	: PcbServo(), _controller(&controller), _servo(servo), _enabled(false), _lastPulse(1500)
{
	
}

void TwiPcbServo::setPulse(uint16_t us){
	_lastPulse = us;
	if(_enabled) _controller->setPulse(_servo, us);
}

void TwiPcbServo::enable(bool en /* = true */){
	_enabled = en;
	if(en) _controller->setPulse(_servo, _lastPulse);
	else _controller->release(_servo);
}
