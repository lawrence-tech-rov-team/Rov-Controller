/*
 * PressureSensor.cpp
 *
 * Created: 3/10/2020 4:34:17 PM
 *  Author: zcarey
 */ 

#include "PressureSensor.h"
#include "../Robot.h"

PressureSensor::PressureSensor(const uint8_t id, HardwareTimer &timer) : sensor(timer), _id(id) {
	
}

bool PressureSensor::begin(){
	if(!rov.RegisterDevice(_id, this)) return false;
	if(sensor.begin()){
		sensor.setModel(MS5837::MS5837_30BA);
		//sensor.setFluidDensity(997); //Freshwater
		return true;
	}
	
	return false;
}

void PressureSensor::Update(uint8_t* buffer){
	if(reading){
		sensor.update();
		if(sensor.finished()){
			saveFloat(sensor.pressure(), buffer);
			saveFloat(sensor.temperature(), buffer + 4);
			SendCommand(_id, 8);
			reading = false;
		}
	}
}

void PressureSensor::ReadRegisterRequested(uint8_t id, uint8_t* buffer){
	if(!reading){
		reading = sensor.startRead();
	}
}