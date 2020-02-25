/*
 * ImuSensor.h
 *
 * Created: 2/19/2020 4:53:15 PM
 *  Author: zcarey
 */ 


#ifndef IMUSENSOR_H_
#define IMUSENSOR_H_

#include "../BNO055/Adafruit_BNO055.h"
#include "../ISensor.h"

#define IMU_SENSOR_BIT_TEMP 0x01
#define IMU_SENSOR_BIT_MAGNETOMETER 0x02
#define IMU_SENSOR_BIT_GYROSCOPE 0x04
#define IMU_SENSOR_BIT_EULER 0x08
#define IMU_SENSOR_BIT_ACCELEROMETER 0x10
#define IMU_SENSOR_BIT_LINEARACCEL 0x20
#define IMU_SENSOR_BIT_GRAVITY 0x40
#define IMU_SENSOR_BIT_QUATERNION 0x80

class ImuSensor : public ISensor{
public:
	ImuSensor(uint8_t ID);
	
	bool begin(); //override

protected:
	bool IsValidRequest(const uint8_t* data, uint8_t len) { //override
		return len == 0;
	}

	//using ISensor::UpdateRequested(uint8_t* buffer, uint8_t mask);
	uint8_t UpdateRequested(uint8_t* buffer, uint8_t mask); //override

private:
	Adafruit_BNO055 imu;
};


#endif /* IMUSENSOR_H_ */