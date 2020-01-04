/*
 * RovController.cpp
 *
 * Created: 12/31/2019 6:51:24 PM
 * Author : zcarey
 */ 

#include "PinDefinitions.h"
#include "EtherComm.h"
#include "Peripherals/HardwareSerial.h"


int main(void){
	Serial.begin(9600);
	Serial.println("\nInitializing...");
	
	
	if(!EtherComm::begin((uint16_t)6001, (uint16_t)6002, EthernetDDR, EthernetPort, EthernetPin_CS)){
		Serial.println("Failed to access Ethernet controller.");
		while(1);
	}
	Serial.println("Connected to controller.");
	
    /* Replace with your application code */
    while (1) {
		EtherComm::Loop();
    }
}

