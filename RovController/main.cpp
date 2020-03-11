/*
 * RovController.cpp
 *
 * Created: 12/31/2019 6:51:24 PM
 * Author : zcarey
 */ 

#include "PinDefinitions/PCBPins.h"
#include "EtherComm.h"
#include "Peripherals/HardwareSerial.h"
#include "Robot.h"
#include "TestIMU.h"
#include <avr/interrupt.h>
#include "Peripherals/HardwareServo.h"
#include "PCA9685/TwiServoController.h"
#include "MS5837/MS5837.h"

int8_t dir = 1;
uint8_t pos = 128;
#include "Utils/CpuFreq.h"
#include <util/delay.h>

TwiServoController TwiServo(0x40);
#define MIN 550
#define MAX 2400

int main(void){
	//TestIMU();
	sei(); //Enable global interrupts
	//Serial.begin(9600);
	//Serial.println("\nInitializing...");
	
	/*if(!rov.begin()){
		Serial.println("Failed to initialize robot.");
		while(1);
	}
	Serial.println("Robot initialized.");
	*/
	/*if(!PressureSensor.begin()){
		Serial.println("Failed to initialize pressure sensor.");
		while(1);
	}*/ //TODO send error codes for intialization debugging
	
	//Serial.println("Initialized pressure sensor.");
	/*
	if(!EtherComm::begin((uint16_t)6001, (uint16_t)6002, DDR_ENC, PORT_ENC, MASK_ENC_CS)){
		Serial.println("Failed to access Ethernet controller.");
		while(1);
	}
	Serial.println("Connected to controller.");*/
	
	//Should no longer be needed. Needs tested first tho
	DDRB |= _BV(PINB5) | _BV(PINB6);
	DDRE |= _BV(PINE3) | _BV(PINE4) | _BV(PINE5);
	DDRH |= _BV(PINH3) | _BV(PINH4) | _BV(PINH5);
	DDRL |= _BV(PINL3) | _BV(PINL4) | _BV(PINL5);
	
	Servo1.begin();
	Servo3.begin();
	Servo4.begin();
	Servo5.begin();
	/*
	Servo_A1_setMin(MIN);
	Servo_A1_setMax(MAX);
	Servo_A1_enable();
	*/
	Servo5.setMinC(MIN);
	Servo5.setMaxC(MAX);
	Servo5.EnableC();
	/*
	Servo1.begin();
	Servo1.setMinA(MIN);
	Servo1.setMinB(MIN);
	//Servo1.setMinC(MIN);
	Servo1.setMaxA(MAX);
	Servo1.setMaxB(MAX);
	Servo1.setMaxC(MAX);
	Servo1.EnableA();
	Servo1.EnableB();
	Servo1.EnableC();
	
	Servo3.begin();
	Servo3.setMinA(MIN);
	Servo3.setMinB(MIN);
	Servo3.setMinC(MIN);
	Servo3.setMaxA(MAX);
	Servo3.setMaxB(MAX);
	Servo3.setMaxC(MAX);
	Servo3.EnableA();
	Servo3.EnableB();
	Servo3.EnableC();
	
	Servo4.begin();
	Servo4.setMinA(MIN);
	Servo4.setMinB(MIN);
	Servo4.setMinC(MIN);
	Servo4.setMaxA(MAX);
	Servo4.setMaxB(MAX);
	Servo4.setMaxC(MAX);
	Servo4.EnableA();
	Servo4.EnableB();
	Servo4.EnableC();
	
	Servo5.begin();
	Servo5.setMinA(MIN);
	Servo5.setMinB(MIN);
	Servo5.setMinC(MIN);
	Servo5.setMaxA(MAX);
	Servo5.setMaxB(MAX);
	Servo5.setMaxC(MAX);
	Servo5.EnableA();
	Servo5.EnableB();
	Servo5.EnableC();
	*/
    /* Replace with your application code */
	//TwiServo.begin();
    while (1) {
		//EtherComm::Loop();
		//rov.Loop();
		//Servo_A1_setPulse(pos);
		Servo5.setPulseC(pos);
/*		Servo1.setPulseA(pos);
		Servo1.setPulseB(pos);
		Servo1.setPulseC(pos);
		Servo3.setPulseA(pos);
		Servo3.setPulseB(pos);
		Servo3.setPulseC(pos);
		Servo4.setPulseA(pos);
		Servo4.setPulseB(pos);
		Servo4.setPulseC(pos);
		Servo5.setPulseA(pos);
		Servo5.setPulseB(pos);
		Servo5.setPulseC(pos);
		*/
		pos += dir;
		if(pos == 255){
			dir = -1;
			_delay_ms(500);
		} else if(pos == 0) {
			dir = 1;
			_delay_ms(500);
		}
		_delay_ms(5);
		//TwiServo.sweep();
		//Serial.print("Pressure: ");
		//PressureSensor.read();
		//Serial.print(PressureSensor.pressure());
		//Serial.println(" mbar");
    }
}

