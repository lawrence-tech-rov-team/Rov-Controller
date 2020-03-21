/*
 * HardwarePcbServo.h
 *
 * Created: 3/20/2020 7:21:04 PM
 *  Author: zcarey
 */ 


#ifndef HARDWAREPCBSERVO_H_
#define HARDWAREPCBSERVO_H_


#include <inttypes.h>
#include <stdbool.h>
#include "PcbServo.h"
#include "../Micro/Peripherals/HardwareServo.h"

class HardwarePcbServo : public PcbServo {
public:
	typedef enum {
		ServoA,
		ServoB,
		ServoC
	} ServoId_t;

	HardwarePcbServo(HardwareServo &controller, ServoId_t servo);
	//void begin();
	void setPulse(uint16_t us); //Override
	void enable(bool en = true); //Override
	//inline void disable(){ enable(false); }

private:
	HardwareServo* _controller;
	ServoId_t _servo;

};


#endif /* HARDWAREPCBSERVO_H_ */