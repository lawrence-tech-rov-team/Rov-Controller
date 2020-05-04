/*
 * Robot.h
 *
 * Created: 3/20/2020 10:52:45 PM
 *  Author: zcarey
 */ 


#ifndef ROBOT_H_
#define ROBOT_H_

#include "Micro/Pins.h"
#include "IRegister.h"

#define NUM_DEVICES 256

class Robot{
public:
	static bool begin();
	static void CheckErrorsOnly();
	static void Loop();
	//static void CommandReceived(const uint8_t* data, uint8_t len);
	static void CommandReceived(const uint8_t id, const uint8_t* data, uint8_t len);
	
	static bool RegisterDevice(uint8_t id, IRegister* device);
	
private:
	Robot(){}
	static IRegister* registers[NUM_DEVICES];
	
};

extern Robot rov;

#endif /* ROBOT_H_ */