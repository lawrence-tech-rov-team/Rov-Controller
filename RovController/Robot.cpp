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

#include "Sensors/DigitalSensor.h"
#include "Sensors/PressureSensor.h"
#include "Sensors/ImuSensor.h"

#include "Actuators/DigitalActuator.h"
#include "Actuators/ServoActuator.h"

IDevice* Robot::registers[NUM_DEVICES];

DigitalSensor Button0(0, DDR_BTN0, PORT_BTN0, PIN_BTN0, MASK_BTN0);
DigitalSensor Button1(9, DDR_BTN1, PORT_BTN1, PIN_BTN1, MASK_BTN1);
DigitalActuator LED(10, DDR_LED, PORT_LED, MASK_LED);
ImuSensor Imu(1, 2);
PressureSensor Pressure(4, Timer0);
ServoActuator TestServo(5, 6, ServoA1);
ServoActuator TestServo2(7, 8, ServoC1);

bool Robot::begin(){
	for(uint16_t i = 0; i < NUM_DEVICES; i++){
		registers[i] = NULL;
	}
	
	if(!EtherComm::begin(6001, 6002, DDR_ENC, PORT_ENC, MASK_ENC_CS)){
		Serial.println("Failed to access Ethernet controller.");
		return false;
	}
	Serial.println("Connected to controller.");
	
	Servo1.begin();
	Servo3.begin();
	Servo4.begin();
	Servo5.begin();
	Serial.println("Servos initialized.");
	
	if(!PcaServoController.begin()){
		Serial.println("Unable to initialize Twi Servo Controller.");
		return false;
	}
	Serial.println("Initialized Twi Servo Controller.");
	
	/*
	//TODO if robot can't be initialized, send diagnostics over ethernet?
	if(!PcaServoController.begin()){
		Serial.println("Unable to initialize Twi Servo Controller");
		return false;
	}
	*/
	//LedDDR |= LedPin;
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
	
	if(!TestServo.begin() || !TestServo2.begin()){
		Serial.println("Unable to initialize Servo.");
		return false;
	}
	Serial.println("Initialized test servo.");
	
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
	Imu.Update(EtherComm::buffer + 3);
	Pressure.Update(EtherComm::buffer + 3);
	//TestServo.Update(EtherComm::buffer + 3);
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
