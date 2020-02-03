/*
 * ISensor.h
 *
 * Created: 2/2/2020 4:41:53 PM
 *  Author: zcarey
 */ 


#ifndef ISENSOR_H_
#define ISENSOR_H_

#include <stdint.h>
#include "IDevice.h"
#include "EtherComm.h"
#include "Commands.h" 


#define SENSOR_TYPE_IMU 0
#define SENSOR_TYPE_DIGITAL 1

class ISensor : public IDevice {
	public:
		void Update(const uint8_t* data, uint8_t len) { //override
			if(len > 0){
				uint8_t type = data[0];
				if(type == sensorType){
					if(IsValidRequest(data + 1, len - 1)){
						EtherComm::buffer[2] = getId(); //TODO does this really have to be called?
						EtherComm::buffer[3] = sensorType;
						len = UpdateRequested(EtherComm::buffer + 4);
						EtherComm::SendCommand(CMD_UpdateDevice, len +  2);
					}
				}
			}
		}
	
	protected:
		ISensor(uint8_t ID, uint8_t type) : IDevice(ID), sensorType(type) {
			
		}
		
		virtual bool IsValidRequest(const uint8_t* data, uint8_t len) = 0;
		
		virtual uint8_t UpdateRequested(uint8_t* buffer) = 0;
		
	private:
		uint8_t sensorType;
};


#endif /* ISENSOR_H_ */