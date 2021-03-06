/*
 * Commands.cpp
 *
 * Created: 3/20/2020 11:02:12 PM
 *  Author: zcarey
 */ 

#include "Commands.h"
#include "EtherComm.h"
#include "Robot.h"
#include <stddef.h>

uint8_t* const SendDataBuffer = (uint8_t*)(&EtherComm::buffer[2]);

void RunPingCommand(const uint8_t* data, uint8_t len){
	if(len == 1){
		SendDataBuffer[0] = data[0];
		EtherComm::SendCommand(CMD_Ping, 1);
	}
}

void RunEchoCommand(const uint8_t* data, uint8_t len){
	uint8_t* index = SendDataBuffer;
	uint8_t dataLen = len;
	while(len-- > 0){
		*(index++) = *(data++);
	}
	
	EtherComm::SendCommand(CMD_Echo, dataLen);
}
//TODO remove this command from both devices
void RunLedCommand(const uint8_t* data, uint8_t len){
	if(len == 1){
		uint8_t state = *data;
		if(state <= 1){
			//rov.SetLed(state > 0);
			//todo REMOVE COMMAND
		}
	}
}

void EtherComm::CommandReceived(uint8_t id, const uint8_t* data, uint8_t len){
	//TODO remove useless commands
	//switch(command){
		//case CMD_Ping: RunPingCommand(data, len); break;
		//case CMD_Echo: RunEchoCommand(data, len); break;
		//case CMD_Led: RunLedCommand(data, len); break;
		/*case CMD_UpdateDevice:*/ rov.CommandReceived(id, data, len); //break;
		//default: break;
	//}
}