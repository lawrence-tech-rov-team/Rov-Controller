/*
 * Robot.h
 *
 * Created: 1/4/2020 3:40:48 PM
 *  Author: zcarey
 */ 


#ifndef ROBOT_H_
#define ROBOT_H_


#include "PinDefinitions.h"

class Robot{
public:

	static bool begin();
	static void SetLed(bool illuminate);

private:

	Robot(){}

};

extern Robot rov;

#endif /* ROBOT_H_ */