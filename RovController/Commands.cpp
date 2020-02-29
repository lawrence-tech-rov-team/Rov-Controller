#include "EtherComm.h"
#include "Robot.h"
#include "Commands.h"
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
			rov.SetLed(state > 0);
		}
	}
}

void EtherComm::CommandReceived(uint8_t command, const uint8_t* data, uint8_t len){
  switch(command){
    case CMD_Ping: RunPingCommand(data, len); break;
    case CMD_Echo: RunEchoCommand(data, len); break;
	case CMD_Led: RunLedCommand(data, len); break;
	case CMD_UpdateDevice: rov.CommandReceived(data, len); break;
    default: break;
  }
}
