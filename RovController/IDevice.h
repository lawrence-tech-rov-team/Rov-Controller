/*
 * IDevice.h
 *
 * Created: 2/28/2020 8:07:17 PM
 *  Author: zcarey
 */ 


#ifndef IDEVICE_H_
#define IDEVICE_H_

#include "EtherComm.h"
#include "Commands.h"

class IDevice{
public:

	virtual bool begin() = 0;
	virtual void CommandReceived(uint8_t id, const uint8_t* data, uint8_t len) = 0;
	virtual void Update(uint8_t* buffer) = 0;
	
protected:
	void inline SendCommand(uint8_t id, uint8_t len){
		EtherComm::buffer[2] = id;
		EtherComm::SendCommand(CMD_UpdateDevice, len + 1);
	}
	
private:	
};


#endif /* IDEVICE_H_ */