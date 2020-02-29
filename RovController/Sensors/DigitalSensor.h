/*
 * DigitalSensor.h
 *
 * Created: 2/2/2020 9:20:49 PM
 *  Author: zcarey
 */ 


#ifndef DIGITALSENSOR_H_
#define DIGITALSENSOR_H_

#include "../IReadable.h"

class DigitalSensor : public IReadable {
public:
	DigitalSensor(const uint8_t ID, Register& DDRPort, Register& PortPort, Register& PinPort, uint8_t Pin, bool Inversed = true) : _id(ID), pin(Pin), pinPort(&PinPort), inversed(Inversed) {
		DDRPort &= ~pin; //Enable input
		PortPort |= pin; //Enable pullup
		rov.RegisterDevice(0, this);
		//TODO move to begin?
	}
	
	bool begin(){ //override
		return rov.RegisterDevice(_id, this);
	}
	
	void Update(uint8_t* buffer) { //override
		
	}

protected:

	void ReadRegisterRequested(uint8_t id, uint8_t* buffer) { //override
		/*Serial.print("My id: ");
		Serial.print(_id);
		Serial.print("    Reg id: ");
		Serial.println(id);*/
		if(id == _id){
			buffer[0] = ((*pinPort & pin) > 0) ^ inversed;
			SendCommand(id, 1);
		}
	}

private:
	const uint8_t _id;
	const uint8_t pin;
	Register* const pinPort;
	const bool inversed;
};


#endif /* DIGITALSENSOR_H_ */