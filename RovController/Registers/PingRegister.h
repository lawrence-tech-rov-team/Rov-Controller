/*
 * PingRegister.h
 *
 * Created: 3/21/2020 7:30:16 PM
 *  Author: zcarey
 */ 


#ifndef PINGREGISTER_H_
#define PINGREGISTER_H_

#include "../IRegister.h"
#include "../EtherComm.h"
#include "../Robot.h"

class PingRegister : public IRegister{
public:	
	PingRegister(const uint8_t id) : _id(id){
		
	}
	
	bool begin(){
		return rov.RegisterDevice(_id, this);
	}
	
	void Update(uint8_t* buffer){
		
	}

	void CommandReceived(uint8_t id, const uint8_t* data, uint8_t len){
		if(id == _id){
			uint8_t* buffer = EtherComm::buffer + 3;
			while(len-- > 0)
				*buffer++ = *data++;
			SendCommand(id, len); 
		}
	}

private:
	const uint8_t _id;

};



#endif /* PINGREGISTER_H_ */