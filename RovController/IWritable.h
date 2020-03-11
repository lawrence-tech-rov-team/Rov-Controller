/*
 * IWritable.h
 *
 * Created: 2/28/2020 8:48:55 PM
 *  Author: zcarey
 */ 


#ifndef IWRITABLE_H_
#define IWRITABLE_H_

#include "IDevice.h"
#include "Commands.h"

class IWritable : public IDevice {
public:
	inline void CommandReceived(uint8_t id, const uint8_t* data, uint8_t len){
		//if(len == 0){
			WriteRegisterRequested(id, data, len);
		//}
	}

protected:
	virtual void WriteRegisterRequested(uint8_t id, const uint8_t* data, uint8_t len);
	void SendConfirmation(uint8_t id){
		EtherComm::buffer[2] = id;
		EtherComm::SendCommand(CMD_UpdateDevice, 1);
	}
	
private:
};


#endif /* IWRITABLE_H_ */