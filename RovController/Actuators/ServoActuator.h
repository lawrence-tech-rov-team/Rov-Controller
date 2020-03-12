/*
 * Servo.h
 *
 * Created: 3/11/2020 10:15:52 AM
 *  Author: zcarey
 */ 


#ifndef SERVOACTUATOR_H_
#define SERVOACTUATOR_H_

#include "../IWritable.h"
#include "../Peripherals/HardwareServo.h"
#include "../PinDefinitions/PCBPins.h"

class ServoActuator : public IWritable {
public:
	ServoActuator(const uint8_t id, const uint8_t minId, const uint8_t maxId, const uint8_t enId)
		: _id(id), _minId(minId), _maxId(maxId), _enId(enId)
	{
		
	}
	
	bool begin(){ //Override
		if(!rov.RegisterDevice(_id, this)) return false;
		if(!rov.RegisterDevice(_minId, this)) return false;
		if(!rov.RegisterDevice(_maxId, this)) return false;
		if(!rov.RegisterDevice(_enId, this)) return false;
		
		Servo_A2_setMin(550);
		Servo_A2_setMax(2400);
		Servo_A2_setPulse(127);
		//Servo_A2_setPulse(0);
		Servo_A2_enable();
		
		return true;	
	}
	
	void Update(uint8_t* buffer){ //Override
		
	}
	
protected:
	void WriteRegisterRequested(uint8_t id, const uint8_t* data, uint8_t len){ //Override
		if(id == _id){
			if(len == 1){
				//lastPos = data[0];
				//Servo_A2_setPulse(data[0]);
				//Servo_A2_setPulse(lastPos++);
				//Servo_A2_setPulse(255);
				SendConfirmation(id);
			}
		}else if(id == _minId){
			if(len == 2){
				//Servo_A2_setMin(*((uint16_t*)data));
				//Servo_A2_setPulse(lastPos);
				SendConfirmation(id);
			}
		}else if(id == _maxId){
			if(len == 2){
				//Servo_A2_setMax(*((uint16_t*)data));
				//Servo_A2_setPulse(lastPos);
				SendConfirmation(id);
			}
		}else if(id == _enId){
			if(len == 1){
				//if(data[0] == 0) Servo_A2_disable();
				//else Servo_A2_enable();
				SendConfirmation(id);
			}
		}
	}
	
private:
	const uint8_t _id;
	const uint8_t _minId;
	const uint8_t _maxId;
	const uint8_t _enId;

	uint8_t lastPos;
};


#endif /* SERVOACTUATOR_H_ */