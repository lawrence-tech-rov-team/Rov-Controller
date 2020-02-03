/*
 * Robot.h
 *
 * Created: 1/4/2020 3:40:48 PM
 *  Author: zcarey
 */ 


#ifndef ROBOT_H_
#define ROBOT_H_


#include "PinDefinitions.h"
#include "IDevice.h"
#include "ISensor.h"

#define NUM_DEVICES 256

class Robot{
public:
	static bool begin();
	static void SetLed(bool illuminate);
	static bool ReadTestBtn();
	static IDevice* devices[NUM_DEVICES];
	
private:
	Robot(){}
	static bool RegisterDevices();
	static void RegisterDevice(ISensor& sensor);

};

extern Robot rov;

#endif /* ROBOT_H_ */