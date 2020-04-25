/*
 * ImuSensor.h
 *
 * Created: 2/19/2020 4:53:15 PM
 *  Author: zcarey
 */ 


#ifndef IMUSENSOR_H_
#define IMUSENSOR_H_

#include "../BNO055/Adafruit_BNO055.h"
#include "../IReadable.h"

class ImuSensor : public IReadable{
public:
	ImuSensor(const uint8_t TempId, const uint8_t AccelId, const uint8_t MagId, const uint8_t GyroId, const uint8_t EulerId, const uint8_t LinearId, const uint8_t GravityId, const uint8_t QuatId);
	
	bool begin(); //override
	
	void Update(uint8_t* buffer); //override

protected:
	void ReadRegisterRequested(uint8_t id, uint8_t* buffer); //override

private:
	Adafruit_BNO055 imu;
	const uint8_t tempId;
	const uint8_t accelId;
	const uint8_t magId;
	const uint8_t gyroId;
	const uint8_t eulerId;
	const uint8_t linearId;
	const uint8_t gravityId;
	const uint8_t quatId;
};


#endif /* IMUSENSOR_H_ */