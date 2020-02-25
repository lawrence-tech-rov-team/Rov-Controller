/*
 * ImuSensor.cpp
 *
 * Created: 2/19/2020 8:49:46 PM
 *  Author: zcarey
 */ 

#include "ImuSensor.h"
//#include "../BNO055/utility/vector.h"
//Adafruit_BNO055 ImuSensor::imu;

ImuSensor::ImuSensor(uint8_t ID) : ISensor(ID, SENSOR_TYPE_DIGITAL), imu(55, 0x28) {
	
}

bool ImuSensor::begin(){
	return imu.begin();
}

static void saveFloat(float f, uint8_t* buffer){
	uint8_t* val = (uint8_t*)(&f);
	*buffer++ = *val++;
	*buffer++ = *val++;
	*buffer++ = *val++;
	*buffer++ = *val++;
}

AdafruitImu::Vector<3> vector;

uint8_t ImuSensor::UpdateRequested(uint8_t* buffer){
	buffer[0] = 0b01111111;
	buffer[1] = imu.getTemp();
	
	vector = imu.getVector(Adafruit_BNO055::VECTOR_EULER);
	saveFloat(vector.x(), buffer + 2);
	saveFloat(vector.y(), buffer + 6);
	saveFloat(vector.z(), buffer + 10);
	
	vector = imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER );
	saveFloat(vector.x(), buffer + 14);
	saveFloat(vector.y(), buffer + 18);
	saveFloat(vector.z(), buffer + 22);
	
	return 1 + 1 + 6*4;
}