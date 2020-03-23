/*
 * FromScrathRovController.cpp
 *
 * Created: 3/20/2020 3:44:59 PM
 * Author : zcarey
 */ 

#include "Micro/Peripherals/HardwareSerial.h"
#include "Robot.h"

int main(void)
{
	Serial.begin(115200);
	Serial.println("Initializing...");
	
	if(!rov.begin()){
		Serial.println("Failed to initialize robot.");
		while(true) ;
	}
	Serial.println("Initialized robot.");
	
    while (1) {
		rov.Loop();
    }
}

