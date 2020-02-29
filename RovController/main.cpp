/*
 * RovController.cpp
 *
 * Created: 12/31/2019 6:51:24 PM
 * Author : zcarey
 */ 

#include "PinDefinitions.h"
#include "EtherComm.h"
#include "Peripherals/HardwareSerial.h"
#include "Robot.h"
#include "TestIMU.h"
#include <avr/interrupt.h>

int main(void){
	//TestIMU();
	sei(); //Enable global interrupts
	Serial.begin(9600);
	Serial.println("\nInitializing...");
	
	if(!rov.begin()){
		Serial.println("Failed to initialize robot.");
		while(1);
	}
	Serial.println("Robot initialized.");
	
	if(!EtherComm::begin((uint16_t)6001, (uint16_t)6002, EthernetDDR, EthernetPort, EthernetPin_CS)){
		Serial.println("Failed to access Ethernet controller.");
		while(1);
	}
	Serial.println("Connected to controller.");
	
    /* Replace with your application code */
    while (1) {
		EtherComm::Loop();
		rov.Loop();
    }
}

