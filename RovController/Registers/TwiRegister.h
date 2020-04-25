/*
 * TwiRegister.h
 *
 * Created: 4/25/2020 1:16:40 PM
 *  Author: Zack
 */ 


#ifndef TWIREGISTER_H_
#define TWIREGISTER_H_

#include "../Micro/Peripherals/Wire.h"

class TwiRegister : public IWritable {
public:
	TwiRegister(const uint8_t id) : _id(id) {
	}
	
	bool begin(){
		return rov.RegisterDevice(_id, this);
	}
	
	void Update(uint8_t* buffer){
		
	}
	
protected:
	void WriteRegisterRequested(uint8_t id, const uint8_t* data, uint8_t len){
		if(id == _id){
			if(len == 4){
				Wire.setClock(*((uint32_t*)data));
			}
		}
	}

private:
	const uint8_t _id;
	//uint32_t freq = 100000L;

};



#endif /* TWIREGISTER_H_ */