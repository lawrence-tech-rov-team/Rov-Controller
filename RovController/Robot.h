/*
 * Robot.h
 *
 * Created: 3/20/2020 10:52:45 PM
 *  Author: zcarey
 */ 


#ifndef ROBOT_H_
#define ROBOT_H_

#include "PcbPins/PcbPins.h"
#include "IDevice.h"

#define NUM_DEVICES 256

class Robot{
public:
	static bool begin();
	static void Loop();
	static void CommandReceived(const uint8_t* data, uint8_t len);	
	
	//static void SetLed(bool illuminate);
	//static bool ReadTestBtn();
	//static IDevice* devices[NUM_DEVICES];
	static IDevice* registers[NUM_DEVICES];
	
	static bool RegisterDevice(uint8_t id, IDevice* device);
	
private:
	Robot(){}
	//static bool RegisterDevices();

};

extern Robot rov;

#endif /* ROBOT_H_ */