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

class ImuSensor : public ISensor{
public:
	ImuSensor(uint8_t ID) : ISensor(ID, SENSOR_TYPE_DIGITAL) {
		
	}

protected:
	bool IsValidRequest(const uint8_t* data, uint8_t len) { //override
		return len == 0;
	}

	uint8_t UpdateRequested(uint8_t* buffer); //override

private:
	Adafruit_BNO055 imu;
};


#endif /* IMUSENSOR_H_ */