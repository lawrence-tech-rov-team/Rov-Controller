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
AdafruitImu::Quaternion quat;
uint8_t ImuSensor::UpdateRequested(uint8_t* buffer, uint8_t mask){
	uint8_t len = 1;
	buffer[0] = 0;
	
	if(mask & IMU_SENSOR_BIT_TEMP){
		buffer[0] |= IMU_SENSOR_BIT_TEMP;
		buffer[len++] = imu.getTemp();
	}
	if(mask & IMU_SENSOR_BIT_MAGNETOMETER){
		buffer[0] |= IMU_SENSOR_BIT_MAGNETOMETER;
	
		vector = imu.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
		saveFloat(vector.x(), &buffer[len]);
		saveFloat(vector.y(), &buffer[len + 4]);
		saveFloat(vector.z(), &buffer[len + 8]);
		len += 12;
	}
	if(mask & IMU_SENSOR_BIT_GYROSCOPE){
		buffer[0] |= IMU_SENSOR_BIT_GYROSCOPE;
		
		vector = imu.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
		saveFloat(vector.x(), &buffer[len]);
		saveFloat(vector.y(), &buffer[len + 4]);
		saveFloat(vector.z(), &buffer[len + 8]);
		len += 12;
	}
	if(mask & IMU_SENSOR_BIT_EULER){
		buffer[0] |= IMU_SENSOR_BIT_EULER;
		
		vector = imu.getVector(Adafruit_BNO055::VECTOR_EULER);
		saveFloat(vector.x(), &buffer[len]);
		saveFloat(vector.y(), &buffer[len + 4]);
		saveFloat(vector.z(), &buffer[len + 8]);
		len += 12;
	}
	if(mask & IMU_SENSOR_BIT_ACCELEROMETER){
		buffer[0] |= IMU_SENSOR_BIT_ACCELEROMETER;
		
		vector = imu.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
		saveFloat(vector.x(), &buffer[len]);
		saveFloat(vector.y(), &buffer[len + 4]);
		saveFloat(vector.z(), &buffer[len + 8]);
		len += 12;
	}
	if(mask & IMU_SENSOR_BIT_LINEARACCEL){
		buffer[0] |= IMU_SENSOR_BIT_LINEARACCEL;
		
		vector = imu.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
		saveFloat(vector.x(), &buffer[len]);
		saveFloat(vector.y(), &buffer[len + 4]);
		saveFloat(vector.z(), &buffer[len + 8]);
		len += 12;
	}
	if(mask & IMU_SENSOR_BIT_GRAVITY){
		buffer[0] |= IMU_SENSOR_BIT_GRAVITY;
		
		vector = imu.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
		saveFloat(vector.x(), &buffer[len]);
		saveFloat(vector.y(), &buffer[len + 4]);
		saveFloat(vector.z(), &buffer[len + 8]);
		len += 12;
	}
	if(mask & IMU_SENSOR_BIT_QUATERNION){
		buffer[0] |= IMU_SENSOR_BIT_QUATERNION;
		
		quat = imu.getQuat();
		saveFloat(quat.w(), &buffer[len]);
		saveFloat(quat.x(), &buffer[len + 4]);
		saveFloat(quat.y(), &buffer[len + 8]);
		saveFloat(quat.z(), &buffer[len + 12]);
		len += 16;
	}
	
	return len;
}