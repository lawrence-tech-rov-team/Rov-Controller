#include "EtherComm.h"

uint8_t* const SendDataBuffer = (uint8_t*)(&EtherComm::buffer[2]);

#define CMD_PING 0
#define CMD_ECHO 1

void RunPingCommand(const uint8_t* data, uint8_t len){
  if(len == 1){
    SendDataBuffer[0] = data[0];
    EtherComm::SendCommand(CMD_PING, 1);
  }
}

void RunEchoCommand(const uint8_t* data, uint8_t len){
  uint8_t* index = SendDataBuffer;
  uint8_t dataLen = len;
  while(len-- > 0){
    *(index++) = *(data++);
  }
  
  EtherComm::SendCommand(CMD_ECHO, dataLen);
}

void EtherComm::CommandReceived(uint8_t command, const uint8_t* data, uint8_t len){
  switch(command){
    case CMD_PING: RunPingCommand(data, len); break;
    case CMD_ECHO: RunEchoCommand(data, len); break;
    default: break;
  }
}
