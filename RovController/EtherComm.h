#ifndef ETHER_COMM_H
#define ETHER_COMM_H

#include "PinDefinitions/PCBPins.h"
#include "EtherCardModified/EtherCard.h"

#define BUFFER_SIZE 258 //Start byte, command byte, 255 data bytes, checksum byte
#define CHECKSUM_MASK 0xFF
#define START_BYTE 0xFF

class EtherComm{
public:

  static bool begin(uint16_t recvPort, uint16_t destPort, Register& csDDR, Register& csPort, uint8_t csPin);

  friend void udpReceive(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len);

  static void Loop(){
    ether.packetLoop(ether.packetReceive());
  }

  static void SendCommand(uint8_t cmd, uint8_t len);

  //static char buffer[];
  static uint8_t* buffer;

private:
  static uint8_t _myip[]; //What to set the Arduino ethernet ip address to
  static uint8_t _gwip[]; //Gateway IP address. Not really used, but required.
  static uint8_t _mymac[]; //What to set the Arduino's ethernet mac address to - must be unique on your network
  
  static uint16_t _recvPort;
  static uint16_t _destPort;
  static uint8_t _destIP[]; //Broadcast to all

  static bool CheckChecksum(const char *data, uint8_t len);
  static void CommandReceived(uint8_t command, const uint8_t* data, uint8_t len);
  
  
  EtherComm(){}
};

#endif //ETHER_COMM_H
