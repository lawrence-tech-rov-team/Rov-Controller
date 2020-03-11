/*
 * PressureSensor.h
 *
 * Created: 3/10/2020 4:34:01 PM
 *  Author: zcarey
 */ 


#ifndef PRESSURESENSOR_H_
#define PRESSURESENSOR_H_

#include "../MS5837/MS5837.h"
#include "../IReadable.h"

class PressureSensor : public IReadable {
public:
	PressureSensor(const uint8_t id, HardwareTimer &timer);
	
	bool begin(); //override
	
	void Update(uint8_t* buffer); //override
	
protected:
	void ReadRegisterRequested(uint8_t id, uint8_t* buffer); //override

private:
	MS5837 sensor;
	const uint8_t _id;
	bool reading;
};



#endif /* PRESSURESENSOR_H_ */