/*
 * ServoActuator.h
 *
 * Created: 3/20/2020 11:38:27 PM
 *  Author: zcarey
 */ 


#ifndef SERVOACTUATOR_H_
#define SERVOACTUATOR_H_

#include "../IWritable.h"
#include "../PcbPins/PcbPins.h"
#include "../Micro/CpuFreq.h"

class ServoActuator : public IWritable{
public:
	ServoActuator(const uint8_t id, const uint8_t enId, PcbServo &servo)
		: _id(id), _enId(enId), _servo(&servo)
	{
			
	}
	
	bool begin(){
		if(!rov.RegisterDevice(_id, this) || !rov.RegisterDevice(_enId, this)) return false;
		
		_servo->setPulse(1500);
		return true;
	}
	
	void Update(uint8_t* buffer){
		
	}
	
protected:
	void WriteRegisterRequested(uint8_t id, const uint8_t* data, uint8_t len){
		if(id == _id){
			if(len == 2){
				_servo->setPulse(*((uint16_t*)data));
				SendConfirmation(id);
			}
		} else if(id == _enId){
			if(len == 1){
				_servo->enable(data[0]);
				SendConfirmation(id);
			}
		}
	}

private:
	const uint8_t _id;
	const uint8_t _enId;
	PcbServo* const _servo;

};

#endif /* SERVOACTUATOR_H_ */