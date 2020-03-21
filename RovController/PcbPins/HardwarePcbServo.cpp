/*
 * HardwarePcbServo.cpp
 *
 * Created: 3/20/2020 7:21:11 PM
 *  Author: zcarey
 */ 

#include "HardwarePcbServo.h"

HardwarePcbServo::HardwarePcbServo(HardwareServo &controller, ServoId_t servo) 
	: PcbServo(), _controller(&controller), _servo(servo) {
	
}
/*
void HardwarePcbServo::begin(){
	switch(_servo){
		case Servo1A:
		case Servo1B:
		case Servo1C:
			Servo1.begin();
			break;
		case Servo3A:
		case Servo3B:
		case Servo3C:
			Servo3.begin();
			break;
		case Servo4A:
		case Servo4B:
		case Servo4C:
			Servo4.begin();
			break;
		case Servo5A:
		case Servo5B:
		case Servo5C:
			Servo5.begin();
			break;
		default:
			break;
	}
}*/
#include "../Micro/Peripherals/HardwareSerial.h"
void HardwarePcbServo::setPulse(uint16_t us){
	Serial.println(_servo);
	switch(_servo){
		case ServoA:
			_controller->setPulseA(us);
			break;
		case ServoB:
			_controller->setPulseB(us);
			break;
		case ServoC:
			_controller->setPulseC(us);
			break;
		default:
			break;
	}
}

void HardwarePcbServo::enable(bool en /* = true */){
	switch(_servo){
		case ServoA:
			if(en) _controller->EnableA(); else _controller->DisableA();
			break;
		case ServoB:
			if(en) _controller->EnableB(); else _controller->DisableB();
			break;
		case ServoC:
			if(en) _controller->EnableC(); else _controller->DisableC();
			break;
		default:
			break;
	}
}
