/*
 * FromScrathRovController.cpp
 *
 * Created: 3/20/2020 3:44:59 PM
 * Author : zcarey
 */ 

#include "PcbPins/PcbPins.h"
#include "Micro/CpuFreq.h"
#include "Micro/Peripherals/HardwareSerial.h"
#include "Robot.h"
#include <avr/interrupt.h>

//#include "Micro/Peripherals/HardwareServo.h"

int main(void)
{
	sei();
	Serial.begin(9600);
	Serial.println("Initializing...");
	
	if(!rov.begin()){
		Serial.println("Failed to initialize robot.");
		while(true) ;
	}
	Serial.println("Initialized robot.");
	
	//ServoA1.setPulse(i);
	//ServoA1.enable(true);
	//Servo5.setPulseC(i);
	//Servo5.EnableC();
    while (1) {
		rov.Loop();
		//Serial.println(i++);
		//_delay_ms(2);
		//ServoA1.setPulse(i);
		//Servo5.setPulseC(i);
    }
}

