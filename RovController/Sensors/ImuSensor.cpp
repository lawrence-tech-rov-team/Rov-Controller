/*
 * ImuSensor.cpp
 *
 * Created: 2/19/2020 8:49:46 PM
 *  Author: zcarey
 */ 

#include "ImuSensor.h"

//Adafruit_BNO055 ImuSensor::imu;

uint8_t ImuSensor::UpdateRequested(uint8_t* buffer){
	buffer[0] = imu.getTemp();
	return 1;
}