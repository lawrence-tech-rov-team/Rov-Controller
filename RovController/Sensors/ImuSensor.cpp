/*
 * ImuSensor.cpp
 *
 * Created: 2/19/2020 8:49:46 PM
 *  Author: zcarey
 */ 

#include "ImuSensor.h"
#include "../Robot.h"

ImuSensor::ImuSensor(const uint8_t TempId, const uint8_t AccelId, const uint8_t MagId, const uint8_t GyroId, const uint8_t EulerId, const uint8_t LinearId, const uint8_t GravityId, const uint8_t QuatId) 
	: imu(55, 0x28), tempId(TempId), accelId(AccelId), magId(MagId), gyroId(GyroId), eulerId(EulerId), linearId(LinearId), gravityId(GravityId), quatId(QuatId) 
{
	
}

bool ImuSensor::begin(){
	return 
		rov.RegisterDevice(tempId, this)
		&& rov.RegisterDevice(accelId, this)
		&& rov.RegisterDevice(magId, this)
		&& rov.RegisterDevice(gyroId, this)
		&& rov.RegisterDevice(eulerId, this)
		&& rov.RegisterDevice(linearId, this)
		&& rov.RegisterDevice(gravityId, this)
		&& rov.RegisterDevice(quatId, this)
		&& imu.begin();
}

void ImuSensor::Update(uint8_t* buffer){
	
}

void ImuSensor::ReadRegisterRequested(uint8_t id, uint8_t* buffer){
	if(id == tempId){
		buffer[0] = imu.getTemp();
		SendCommand(id, 1);
	}else if(id == accelId) {
		SendCommand(id, imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER, buffer));
	}else if(id == magId){
		SendCommand(id, imu.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER, buffer));
	}else if(id == gyroId){
		SendCommand(id, imu.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE, buffer));
	}else if(id == eulerId){
		SendCommand(id, imu.getVector(Adafruit_BNO055::VECTOR_EULER, buffer));
	}else if(id == linearId){
		SendCommand(id, imu.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL, buffer));
	}else if(id == gravityId){
		SendCommand(id, imu.getVector(Adafruit_BNO055::VECTOR_GRAVITY, buffer));
	}else if(id == quatId){
		SendCommand(id, imu.getQuat(buffer));
	}
}