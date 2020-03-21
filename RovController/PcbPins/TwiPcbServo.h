/*
 * TwiPcbServo.h
 *
 * Created: 3/21/2020 12:12:08 AM
 *  Author: zcarey
 */ 


#ifndef TWIPCBSERVO_H_
#define TWIPCBSERVO_H_

#include <inttypes.h>
#include <stdbool.h>
#include "PcbServo.h"
#include "../PCA9685/TwiServoController.h"

class TwiPcbServo : public PcbServo {
public:
	TwiPcbServo(TwiServoController &controller, uint8_t servo);
	
	void setPulse(uint16_t us); //Override
	void enable(bool en = true); //Override
	
private:
	TwiServoController* _controller;
	uint8_t _servo;
	bool _enabled;
	uint16_t _lastPulse;

};


#endif /* TWIPCBSERVO_H_ */