/*
 * Robot.cpp
 *
 * Created: 3/20/2020 10:52:56 PM
 *  Author: zcarey
 */ 

#include "Robot.h"
#include "Micro/Peripherals/HardwareSerial.h"
#include <stddef.h>
#include "Micro/CpuFreq.h"
#include "PcbPins/PcbPins.h"

#include "Sensors/DigitalSensor.h"
#include "Sensors/PressureSensor.h"
#include "Sensors/ImuSensor.h"

#include "Actuators/DigitalActuator.h"
#include "Actuators/ServoActuator.h"

IRegister* Robot::registers[NUM_DEVICES];

//ServoActuator A1(0, 1, ServoA1);

DigitalSensor Button0(0, DDR_BTN0, PORT_BTN0, PIN_BTN0, MASK_BTN0);
DigitalSensor Button1(1, DDR_BTN1, PORT_BTN1, PIN_BTN1, MASK_BTN1);
DigitalActuator LED(2, DDR_LED, PORT_LED, MASK_LED);
PressureSensor Pressure(3, Timer0);
ImuSensor Imu(4, 5);

ServoActuator ServoA1(6, 7, PcbServoA1);
ServoActuator ServoA2(8, 9, PcbServoA2);
ServoActuator ServoA3(10, 11, PcbServoA3);
ServoActuator ServoA4(12, 13, PcbServoA4);
ServoActuator ServoA5(14, 15, PcbServoA5);

ServoActuator ServoB1(16, 17, PcbServoB1);
ServoActuator ServoB2(18, 19, PcbServoB2);
ServoActuator ServoB3(20, 21, PcbServoB3);
ServoActuator ServoB4(22, 23, PcbServoB4);
ServoActuator ServoB5(24, 25, PcbServoB5);
ServoActuator ServoB6(26, 27, PcbServoB6);

ServoActuator ServoC1(28, 29, PcbServoC1);
ServoActuator ServoC2(30, 31, PcbServoC2);
ServoActuator ServoC3(32, 33, PcbServoC3);
ServoActuator ServoC4(34, 35, PcbServoC4);
ServoActuator ServoC5(36, 37, PcbServoC5);
ServoActuator ServoC6(38, 39, PcbServoC6);
ServoActuator ServoC7(40, 41, PcbServoC7);
ServoActuator ServoC8(42, 43, PcbServoC8);

ServoActuator ServoD1(44, 45, PcbServoD1);
ServoActuator ServoD2(46, 47, PcbServoD2);
ServoActuator ServoD3(48, 49, PcbServoD3);
ServoActuator ServoD4(50, 51, PcbServoD4);
ServoActuator ServoD5(52, 53, PcbServoD5);
ServoActuator ServoD6(54, 55, PcbServoD6);
ServoActuator ServoD7(56, 57, PcbServoD7);
ServoActuator ServoD8(58, 59, PcbServoD8);

void printServoErrorCode(uint8_t code){
	if(code == 0x01){
		Serial.println("Unable to initialize Twi Servo Controller.");
		return;
	}
	
	char letter = '?';
	uint8_t num = code & 0x0F;
	
	switch(code >> 4){
		case 1: letter = 'A'; break;
		case 2: letter = 'B'; break;
		case 3: letter = 'C'; break;
		case 4: letter = 'D'; break;
	}
	
	Serial.print("Unable to initialize Servo");
	Serial.print(letter);
	Serial.print(num);
	Serial.println(".");
}

bool initializeServos(){
	Servo1.begin();
	Servo3.begin();
	Servo4.begin();
	Servo5.begin();
	
	if(!PcaServoController.begin()) return 0x01;
	Serial.println("Initialized Twi Servo Controller.");
	
	if(!ServoA1.begin()) return 0x11;
	if(!ServoA2.begin()) return 0x12;
	if(!ServoA3.begin()) return 0x13;
	if(!ServoA4.begin()) return 0x14;
	if(!ServoA5.begin()) return 0x15;
	
	if(!ServoB1.begin()) return 0x21;
	if(!ServoB2.begin()) return 0x22;
	if(!ServoB3.begin()) return 0x23;
	if(!ServoB4.begin()) return 0x24;
	if(!ServoB5.begin()) return 0x25;
	if(!ServoB6.begin()) return 0x26;
	
	if(!ServoC1.begin()) return 0x31;
	if(!ServoC2.begin()) return 0x32;
	if(!ServoC3.begin()) return 0x33;
	if(!ServoC4.begin()) return 0x34;
	if(!ServoC5.begin()) return 0x35;
	if(!ServoC6.begin()) return 0x36;
	if(!ServoC7.begin()) return 0x37;
	if(!ServoC8.begin()) return 0x38;
	
	if(!ServoD1.begin()) return 0x41;
	if(!ServoD2.begin()) return 0x42;
	if(!ServoD3.begin()) return 0x43;
	if(!ServoD4.begin()) return 0x44;
	if(!ServoD5.begin()) return 0x45;
	if(!ServoD6.begin()) return 0x46;
	if(!ServoD7.begin()) return 0x47;
	if(!ServoD8.begin()) return 0x48;
	
	return 0;
}

bool Robot::begin(){
	for(uint16_t i = 0; i < NUM_DEVICES; i++){
		registers[i] = NULL;
	}
	
	if(!EtherComm::begin(6001, 6002, DDR_ENC, PORT_ENC, MASK_ENC_CS)){
		Serial.println("Failed to access Ethernet controller.");
		return false;
	}
	Serial.println("Connected to controller.");
	
	uint8_t code = initializeServos();
	if(code != 0){
		printServoErrorCode(code);
		return false;
	}
	Serial.println("Servos initialized.");
	//TODO if robot can't be initialized, send diagnostics over ethernet?
	if(!Button0.begin()){
		Serial.println("Unable to initialize Button0.");
		return false;
	}
	Serial.println("Initialized Button0.");
	
	if(!Button1.begin()){
		Serial.println("Unable to initialize Button1.");
		return false;
	}
	Serial.println("Initialized Button1.");
	
	if(!LED.begin()){
		Serial.println("Unable to initialize LED.");
		return false;
	}
	Serial.println("Initialized LED.");
	
	if(!Imu.begin()){
		Serial.println("Unable to initialize IMU.");
		return false;
	}
	Serial.println("Initialized IMU");
	
	if(!Pressure.begin()){ 
		Serial.println("Unable to initialize Pressure Sensor.");
		return false;
	} 
	Serial.println("Initialized pressure sensor.");
	
	return true;
}


bool Robot::RegisterDevice(uint8_t id, IRegister* device){
	if(registers[id] == NULL){
		//if(sensor.begin()){
		registers[id] = device; //TODO error handling
		//}
		return true;
	}else{
		//TODO id collisions
		return false;
	}
}
/*
void Robot::SetLed(bool illuminate){ //TODO remove
	if(illuminate) LedPort |= LedPin;
	else LedPort &= ~LedPin;
}*/
/*
bool Robot::ReadTestBtn(){ //TODO remove
	return !((TestBtnPinPort & TestBtnPin) > 0);
}*/

void Robot::Loop(){
	EtherComm::Loop();
	Imu.Update(EtherComm::buffer + 1/*3*/);
	Pressure.Update(EtherComm::buffer + 1/*3*/);
	//TestServo.Update(EtherComm::buffer + 1/*3*/);
}

//void Robot::CommandReceived(const uint8_t* data, uint8_t len){
void Robot::CommandReceived(const uint8_t id, const uint8_t* data, uint8_t len) {
	/*Serial.print(len);
	Serial.print(':');
	for(uint8_t i = 0; i < len; i++){
		Serial.print(' ');
		Serial.print(data[i], HEX);
	}
	Serial.println();*/
	//if(len >= 1){
		if(registers[/*data[0]*/id] != NULL){
			registers[/*data[0]*/id]->CommandReceived(/*data[0]*/id, data /*+ 1*/, len/* - 1*/);
		}else{
			//Serial.println("Not found: ");
			//Serial.println(registers[data[0]] == nullptr);
		}
	//}
}
