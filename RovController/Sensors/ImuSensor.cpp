/*
 * ImuSensor.cpp
 *
 * Created: 2/19/2020 8:49:46 PM
 *  Author: zcarey
 */ 

#include "ImuSensor.h"
#include "../Robot.h"

#define ID_TEMP 1
#define ID_ACCEL 2
//#include "../BNO055/utility/vector.h"
//Adafruit_BNO055 ImuSensor::imu;

ImuSensor::ImuSensor(const uint8_t TempId, const uint8_t AccelId) : imu(55, 0x28), tempId(TempId), accelId(AccelId) {
	
}

bool ImuSensor::begin(){
	return 
		rov.RegisterDevice(tempId, this)
		&& rov.RegisterDevice(accelId, this)
		&& imu.begin();
}

void ImuSensor::Update(uint8_t* buffer){
	
}
/*
static void saveFloat(float f, uint8_t* buffer){ //TODO put in IRegister? Used in PressureSensor too
	uint8_t* val = (uint8_t*)(&f);
	*buffer++ = *val++;
	*buffer++ = *val++;
	*buffer++ = *val++;
	*buffer++ = *val++;
}*/

AdafruitImu::Vector<3> vector;

void ImuSensor::ReadRegisterRequested(uint8_t id, uint8_t* buffer){
	if(id == tempId){
		buffer[0] = imu.getTemp();
		SendCommand(id, 1);
	}else if(id == accelId) {
		/*vector = imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER );
		saveFloat(vector.x(), buffer + 0);
		saveFloat(vector.y(), buffer + 4);
		saveFloat(vector.z(), buffer + 8);
		SendCommand(id, 12);*/
		uint8_t bytes = imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER, buffer);
		SendCommand(id, bytes);
	}
/*	vector = imu.getVector(Adafruit_BNO055::VECTOR_EULER);
	saveFloat(vector.x(), buffer + 14);
	saveFloat(vector.y(), buffer + 18);
	saveFloat(vector.z(), buffer + 22);
	
	return 1 + 1 + 6*4;*/
}