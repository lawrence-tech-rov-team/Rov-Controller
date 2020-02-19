/*
 * Robot.cpp
 *
 * Created: 1/4/2020 3:41:02 PM
 *  Author: zcarey
 */ 

#include "Robot.h"

#include "Sensors/DigitalSensor.h"
#include <stddef.h>

IDevice* Robot::devices[NUM_DEVICES];

DigitalSensor BtnTest(0, TestBtnDDR, TestBtnPort, TestBtnPinPort, TestBtnPin);

bool Robot::RegisterDevices(){
	RegisterDevice(BtnTest); //TODO return if successful
	
	return true;
}

void Robot::SetLed(bool illuminate){
	if(illuminate) LedPort |= LedPin;
	else LedPort &= ~LedPin;
}

bool Robot::ReadTestBtn(){
	return !((TestBtnPinPort & TestBtnPin) > 0);
}

bool Robot::begin(){
	LedDDR |= LedPin;
	return RegisterDevices();
}

void Robot::RegisterDevice(ISensor& sensor){
	uint8_t id = sensor.getId();
	if(devices[id] == NULL){
		devices[id] = &sensor;
	}else{
		//TODO id collisions
	}
}

