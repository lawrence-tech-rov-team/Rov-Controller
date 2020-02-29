/*
 * Robot.cpp
 *
 * Created: 1/4/2020 3:41:02 PM
 *  Author: zcarey
 */ 

#include "Robot.h"

#include "Sensors/DigitalSensor.h"
#include "Sensors/ImuSensor.h"
#include <stddef.h>

IDevice* Robot::registers[NUM_DEVICES];

#define ID_TEST_BUTTON 0
#define ID_IMU_TEMPERATURE 1
#define ID_IMU_ACCELEROMETER 2

DigitalSensor BtnTest(0, TestBtnDDR, TestBtnPort, TestBtnPinPort, TestBtnPin);
ImuSensor Imu(1, 2);
/*
bool Robot::RegisterDevices(){
	RegisterDevice(BtnTest); //TODO return if successful
	RegisterDevice(Imu);
	
	return true;
}*/

bool Robot::begin(){
	for(uint16_t i = 0; i < NUM_DEVICES; i++){
		registers[i] = NULL;
	}
	
	LedDDR |= LedPin;
	BtnTest.begin();
	Imu.begin();
	return true;
}


bool Robot::RegisterDevice(uint8_t id, IDevice* device){
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

void Robot::SetLed(bool illuminate){ //TODO remove
	if(illuminate) LedPort |= LedPin;
	else LedPort &= ~LedPin;
}

bool Robot::ReadTestBtn(){ //TODO remove
	return !((TestBtnPinPort & TestBtnPin) > 0);
}

void Robot::Loop(){
	Imu.Update(EtherComm::buffer + 3);
}

void Robot::CommandReceived(const uint8_t* data, uint8_t len){
	/*Serial.print(len);
	Serial.print(':');
	for(uint8_t i = 0; i < len; i++){
		Serial.print(' ');
		Serial.print(data[i], HEX);
	}
	Serial.println();*/
	if(len >= 1){
		if(registers[data[0]] != NULL){
			registers[data[0]]->CommandReceived(data[0], data + 1, len - 1);
		}else{
			//Serial.println("Not found: ");
			//Serial.println(registers[data[0]] == nullptr);
		}
	}
}


