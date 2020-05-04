/*
 * IDevice.h
 *
 * Created: 3/20/2020 10:53:46 PM
 *  Author: zcarey
 */ 


#ifndef IDEVICE_H_
#define IDEVICE_H_

#include "EtherComm.h"
#include "Commands.h"

class IRegister{
public:
	virtual bool begin() = 0;
	virtual void CommandReceived(uint8_t id, const uint8_t* data, uint8_t len) = 0;
	virtual void Update(uint8_t* buffer) = 0;
	
protected:
	void inline SendCommand(uint8_t id, uint8_t len){
		//EtherComm::buffer[2] = id;
		//EtherComm::SendCommand(CMD_UpdateDevice, len + 1);
		EtherComm::SendCommand(id, len);	
	}
	
	static void saveFloat(float f, uint8_t* buffer){ 
		/*uint8_t* val = (uint8_t*)(&f);
		*buffer++ = *val++;
		*buffer++ = *val++;
		*buffer++ = *val++;
		*buffer++ = *val++;*/
		*((float*)buffer) = f;
	}
		
};



#endif /* IDEVICE_H_ */