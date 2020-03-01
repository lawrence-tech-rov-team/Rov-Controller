/*
 * TwiServoController.h
 *
 * Created: 2/29/2020 10:15:49 PM
 *  Author: zcarey
 */ 


#ifndef TWISERVOCONTROLLER_H_
#define TWISERVOCONTROLLER_H_

#include "PCA9685.h"

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

class TwiServoController{
public:
	TwiServoController(const uint8_t addr);
	void begin();
	void sweep();
	
private:
	PCA9685 controller;
	
};

#endif /* TWISERVOCONTROLLER_H_ */