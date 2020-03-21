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
	DigitalSensor(const uint8_t ID, Register& DDRPort, Register& PortPort, Register& PinPort, uint8_t Pin, bool Inversed = true) 
		: _id(ID), _pin(Pin), _pinPort(&PinPort), _inversed(Inversed)
	{
		DDRPort &= ~Pin; //Enable input
		PortPort |= Pin; //Enable pullup
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
			buffer[0] = ((*_pinPort & _pin) > 0) ^ _inversed;
			SendCommand(id, 1);
		}
	}

private:
	const uint8_t _id;
	const uint8_t _pin;
	Register* const _pinPort;
	const bool _inversed;
};


#endif /* DIGITALSENSOR_H_ */