/*
 * EtherComm.cpp
 *
 * Created: 3/20/2020 10:59:07 PM
 *  Author: zcarey
 */ 

#include "EtherComm.h"


uint8_t EtherComm::_myip[] = { 169,254,240,157 }; //What to set the Arduino ethernet ip address to
uint8_t EtherComm::_gwip[] = { 192,168,178,1 }; //Gateway IP address. Not really used, but required.
uint8_t EtherComm::_mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 }; //What to set the Arduino's ethernet mac address to - must be unique on your network
uint8_t EtherComm::_destIP[] = { 255,255,255,255 }; //Broadcast to all

uint16_t EtherComm::_recvPort = 0;
uint16_t EtherComm::_destPort = 0;

//char EtherComm::buffer[BUFFER_SIZE];
uint8_t* EtherComm::buffer = ether.buffer + UDP_DATA_P;

//callback that prints received packets to the serial port
void udpReceive(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t packetLen){
/*  IPAddress src(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);
  ether.printIp(src_ip);*/
/*	Serial.println();
	Serial.print("Start Byte: ");
	Serial.println((uint8_t)data[0]);
	Serial.print("Command: ");
	Serial.println((uint8_t)data[1]);
	
	Serial.print("Data: ");
	const char* index = &data[2];
	uint8_t len = packetLen - 3;
	while(len-- > 0){
		Serial.write(*(index++));
	}
	Serial.println();
	Serial.print("Checksum: ");
	Serial.println((uint8_t)(*index));
*/	
	if(packetLen >= 3){ //At minimum, start byte, command, and checksum.
		if(packetLen <= 258){
			uint8_t dataLen = (uint8_t)(packetLen - 3);
			if((uint8_t)data[0] == START_BYTE){
			//		Serial.print("Computed Checksum: ");
				if(EtherComm::CheckChecksum(data, dataLen)){
					EtherComm::CommandReceived((uint8_t)data[1], (const uint8_t*)(data + 2), dataLen);
				}
			}
		}
	}
}

bool EtherComm::CheckChecksum(const char *data, uint8_t len){
  //data++; //Ignore first byte, the start byte.
  uint8_t checksum = (uint8_t)(*(data++)); //Start by 'adding' the command to the checksum
  checksum += (uint8_t)(*(data++));
  while(len-- > 0){
    checksum += (uint8_t)(*(data++));
  }
//  Serial.println((uint8_t)(checksum & CHECKSUM_MASK));
  return (checksum & CHECKSUM_MASK) == (uint8_t)(*data);
}

bool EtherComm::begin(uint16_t recvPort, uint16_t destPort, Register& csDDR, Register& csPort, uint8_t csPin){
  EtherComm::_recvPort = recvPort;
  EtherComm::_destPort = destPort;
  
  if (ether.begin(EtherComm::_mymac, csDDR, csPort, csPin) == 0) return false;
  ether.staticSetup(EtherComm::_myip, EtherComm::_gwip);
  
  //Serial.println(F("Static IP Setup..."));
  /*
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
  */
  
  //Register the udpSerialPrint() method to listen to port the receive port.
  ether.udpServerListenOnPort(&udpReceive, recvPort);
  
  return true;
}

void EtherComm::SendCommand(uint8_t cmd, uint8_t len){
  EtherComm::buffer[0] = START_BYTE;
  EtherComm::buffer[1] = cmd;
  //EtherComm::buffer[2] = len;
  
  uint8_t checksum = START_BYTE + cmd;
  uint8_t* index = &EtherComm::buffer[2]; //TODO why is char* being used? convert ot uint8_t*!!
  uint8_t bytes = len;
  while(bytes-- > 0){
    checksum += (uint8_t)(*(index++));  
  }
  (*index) = (uint8_t)(checksum & CHECKSUM_MASK);

  //Serial.print("Send: ");
  //Serial.println(len);
  ether.sendUdp(EtherComm::buffer, (uint16_t)len + (uint16_t)3, _recvPort, _destIP, _destPort);
}

