/*
 * IReadable.h
 *
 * Created: 2/28/2020 8:45:40 PM
 *  Author: zcarey
 */ 


#ifndef IREADABLE_H_
#define IREADABLE_H_

#include "IDevice.h"
#include "EtherComm.h"

class IReadable : public IDevice {
public:
	void CommandReceived(uint8_t id, const uint8_t* data, uint8_t len){
		if(len == 0){
			ReadRegisterRequested(id, EtherComm::buffer + 3);
		}
	}

protected:
	virtual void ReadRegisterRequested(uint8_t id, uint8_t* buffer);
	
private:
};


#endif /* IREADABLE_H_ */