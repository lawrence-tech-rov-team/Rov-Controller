/*
 * DigitalSensor.h
 *
 * Created: 2/2/2020 9:20:49 PM
 *  Author: zcarey
 */ 


#ifndef DIGITALSENSOR_H_
#define DIGITALSENSOR_H_

#include "../ISensor.h"

class DigitalSensor : public ISensor{
public:
	DigitalSensor(uint8_t ID, Register& DDRPort, Register& PortPort, Register& PinPort, uint8_t Pin, bool Inversed = true) : ISensor(ID, SENSOR_TYPE_DIGITAL), pin(Pin), pinPort(&PinPort), inversed(Inversed) {
		DDRPort &= ~pin; //Enable input
		PortPort |= pin; //Enable pullup
		//TODO move to begin?
	}
	
	bool begin(){
		return true;
	}

protected:

	bool IsValidRequest(const uint8_t* data, uint8_t len) { //override
		return len == 0;
	}

	uint8_t UpdateRequested(uint8_t* buffer, uint8_t mask) { //override
		buffer[0] = ((*pinPort & pin) > 0) ^ inversed;
		return 1;
	}

private:
	const uint8_t pin;
	Register* const pinPort;
	const bool inversed;
};


#endif /* DIGITALSENSOR_H_ */