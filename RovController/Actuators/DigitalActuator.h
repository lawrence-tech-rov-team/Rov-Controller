/*
 * DigitalActuator.h
 *
 * Created: 3/21/2020 4:05:34 PM
 *  Author: zcarey
 */ 


#ifndef DIGITALACTUATOR_H_
#define DIGITALACTUATOR_H_

#include "../IWritable.h"
class DigitalActuator : public IWritable{
public:
	DigitalActuator(const uint8_t ID, Register& DDRPort, Register& PortPort, uint8_t Pin, bool Inversed = false)
		: _id(ID), _pin(Pin), _portPort(&PortPort), _inversed(Inversed)
	{
		DDRPort |= Pin;
	}
	
	bool begin(){ //override
		return rov.RegisterDevice(_id, this);
	}
	
	void Update(uint8_t* buffer){ //override
		
	}

protected:
	void WriteRegisterRequested(uint8_t id, const uint8_t* data, uint8_t len){ //override
		if((id == _id) && (len == 1)){
			if((data[0] > 0) ^ _inversed) *_portPort |= _pin;
			else *_portPort &= ~_pin;
			SendConfirmation(id);
		}
	}

private:
	const uint8_t _id;
	const uint8_t _pin;
	Register* const _portPort;
	const bool _inversed;

};



#endif /* DIGITALACTUATOR_H_ */