/*
 * IWritable.h
 *
 * Created: 2/28/2020 8:48:55 PM
 *  Author: zcarey
 */ 


#ifndef IWRITABLE_H_
#define IWRITABLE_H_

#include "IDevice.h"

class IWritable : public IDevice {
public:
	void CommandReceived(uint8_t id, const uint8_t* data, uint8_t len){
		if(len == 0){
			WriteRegisterRequested(id, EtherComm::buffer + 3);
		}
	}

protected:
	virtual void WriteRegisterRequested(uint8_t id, uint8_t* buffer);
	
private:
};


#endif /* IWRITABLE_H_ */