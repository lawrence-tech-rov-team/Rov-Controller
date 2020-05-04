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

#include "Registers/TwiRegister.h"

IRegister* Robot::registers[NUM_DEVICES];

ServoActuator ServoA1(0, 1, PcbServoA1); //Position Id, Enable Id
ServoActuator ServoA2(2, 3, PcbServoA2);
ServoActuator ServoA3(4, 5, PcbServoA3);
ServoActuator ServoA4(6, 7, PcbServoA4);
ServoActuator ServoA5(8, 9, PcbServoA5);

ServoActuator ServoB1(10, 11, PcbServoB1);
ServoActuator ServoB2(12, 13, PcbServoB2);
ServoActuator ServoB3(14, 15, PcbServoB3);
ServoActuator ServoB4(16, 17, PcbServoB4);
ServoActuator ServoB5(18, 19, PcbServoB5);
ServoActuator ServoB6(20, 21, PcbServoB6);

ServoActuator ServoC1(22, 23, PcbServoC1);
ServoActuator ServoC2(24, 25, PcbServoC2);
ServoActuator ServoC3(26, 27, PcbServoC3);
ServoActuator ServoC4(28, 29, PcbServoC4);
ServoActuator ServoC5(30, 31, PcbServoC5);
ServoActuator ServoC6(32, 33, PcbServoC6);
ServoActuator ServoC7(34, 35, PcbServoC7);
ServoActuator ServoC8(36, 37, PcbServoC8);

ServoActuator ServoD1(38, 39, PcbServoD1);
ServoActuator ServoD2(40, 41, PcbServoD2);
ServoActuator ServoD3(42, 43, PcbServoD3);
ServoActuator ServoD4(44, 45, PcbServoD4);
ServoActuator ServoD5(46, 47, PcbServoD5);
ServoActuator ServoD6(48, 49, PcbServoD6);
ServoActuator ServoD7(50, 51, PcbServoD7);
ServoActuator ServoD8(52, 53, PcbServoD8);

DigitalSensor Button0(54, DDR_BTN0, PORT_BTN0, PIN_BTN0, MASK_BTN0);
DigitalSensor Button1(55, DDR_BTN1, PORT_BTN1, PIN_BTN1, MASK_BTN1);
DigitalActuator LED(56, DDR_LED, PORT_LED, MASK_LED);

PressureSensor Pressure(57, Timer0);
ImuSensor Imu(
	58, //Temperature Id
	59, //Accelerometer Id
	60, //Magnometer Id
	61, //Gyroscope Id
	62, //Euler Id
	63, //Linear Accelerometer Id
	64, //Gravity Id
	65  //Quaternion
);

TwiRegister TwiSettings(66);

bool initialized = false;

enum ErrorFlag {
	None = 0x00,
	IdCollision = 0x01,
	InitializationError = 0x02,
	RegisterNotFound = 0x04
};

inline ErrorFlag operator | (ErrorFlag lhs, ErrorFlag rhs) {
	return static_cast<ErrorFlag>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

inline ErrorFlag& operator |= (ErrorFlag& lhs, ErrorFlag rhs) {
	lhs = lhs | rhs;
	return lhs;
}

struct ErrorCodeStruct{
	ErrorFlag errors;
	uint8_t id_collision; //The last id collision that occured
	uint8_t init_error; //Code for what device could not be initialized
	uint8_t reg_not_found; //Id of the last register that could not be found
};

ErrorCodeStruct ErrorCodes;

#define ERROR_INIT_BTN0 0x01
#define ERROR_INIT_BTN1 0x02
#define ERROR_INIT_LED 0x03
#define ERROR_INIT_IMU 0x04
#define ERROR_INIT_PRESSURE 0x05
#define ERROR_INIT_TWI 0x06

void printServoErrorCode(uint8_t code){
	if(code == 0x10){
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
	
	if(!PcaServoController.begin()) return 0x10;
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
		ErrorCodes.errors |= InitializationError;
		ErrorCodes.init_error = code;
		printServoErrorCode(code);
		return false;
	}
	Serial.println("Servos initialized.");
	
	if(!Button0.begin()){
		ErrorCodes.errors |= InitializationError;
		ErrorCodes.init_error = ERROR_INIT_BTN0;
		Serial.println("Unable to initialize Button0.");
		return false;
	}
	Serial.println("Initialized Button0.");
	
	if(!Button1.begin()){
		ErrorCodes.errors |= InitializationError;
		ErrorCodes.init_error = ERROR_INIT_BTN1;
		Serial.println("Unable to initialize Button1.");
		return false;
	}
	Serial.println("Initialized Button1.");
	
	if(!LED.begin()){
		ErrorCodes.errors |= InitializationError;
		ErrorCodes.init_error = ERROR_INIT_LED;
		Serial.println("Unable to initialize LED.");
		return false;
	}
	Serial.println("Initialized LED.");
	
	if(!Imu.begin()){
		ErrorCodes.errors |= InitializationError;
		ErrorCodes.init_error = ERROR_INIT_IMU;
		Serial.println("Unable to initialize IMU.");
		return false;
	}
	Serial.println("Initialized IMU");
	
	if(!Pressure.begin()){ 
		ErrorCodes.errors |= InitializationError;
		ErrorCodes.init_error = ERROR_INIT_PRESSURE;
		Serial.println("Unable to initialize Pressure Sensor.");
		return false;
	} 
	Serial.println("Initialized pressure sensor.");
	
	if(!TwiSettings.begin()){
		ErrorCodes.errors |= InitializationError;
		ErrorCodes.init_error = ERROR_INIT_TWI;
		Serial.println("Unable to initialize TWI settings.");
	}
	Serial.println("Initialized settings.");
	
	initialized = true;
	return true;
}


bool Robot::RegisterDevice(uint8_t id, IRegister* device){
	if((id != 0xFF) && (registers[id] == NULL)){
		registers[id] = device; 
		return true;
	}else{
		ErrorCodes.errors |= IdCollision;
		ErrorCodes.id_collision = id;
		return false;
	}
}

void Robot::Loop(){
	EtherComm::Loop();
	Imu.Update(EtherComm::buffer + 1);
	Pressure.Update(EtherComm::buffer + 1);
}

void Robot::CheckErrorsOnly(){
	EtherComm::Loop();
}

void PrintErrorCodes(){
	EtherComm::buffer[1] = ErrorCodes.errors;
	EtherComm::buffer[2] = ErrorCodes.id_collision;
	EtherComm::buffer[3] = ErrorCodes.init_error;
	EtherComm::buffer[4] = ErrorCodes.reg_not_found;
	EtherComm::SendCommand(0xFF, 4);
}

void Robot::CommandReceived(const uint8_t id, const uint8_t* data, uint8_t len) {
	if(id == 0xFF){
		PrintErrorCodes();
	}else if(initialized) { 
		if(registers[id] != NULL){
			registers[id]->CommandReceived(id, data, len);
		}else{
			ErrorCodes.errors |= RegisterNotFound;
			ErrorCodes.reg_not_found = id;
		}
	}
}
