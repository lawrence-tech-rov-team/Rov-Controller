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
	ImuSensor(const uint8_t TempId, const uint8_t AccelId);
	
	bool begin(); //override
	
	void Update(uint8_t* buffer); //override

protected:
	void ReadRegisterRequested(uint8_t id, uint8_t* buffer); //override

private:
	Adafruit_BNO055 imu;
	const uint8_t tempId;
	const uint8_t accelId;
};


#endif /* IMUSENSOR_H_ */