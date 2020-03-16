/*
 * PcbServo.cpp
 *
 * Created: 3/16/2020 6:47:16 PM
 *  Author: zcarey
 */ 

#include "PcbServo.h"
#include "../Peripherals/HardwareServo.h"

PcbServo::PcbServo(ServoId_t servo) : _servo(servo) {
	
}

void PcbServo::begin(){
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
}

void PcbServo::setPulse(uint16_t us){
	switch(_servo){
		case Servo1A:
			Servo1.setPulseA(us);
			break;
		case Servo1B:
			Servo1.setPulseB(us);
			break;
		case Servo1C:
			Servo1.setPulseC(us);
			break;
		case Servo3A:
			Servo3.setPulseA(us);
			break;
		case Servo3B:
			Servo3.setPulseB(us);
			break;
		case Servo3C:
			Servo3.setPulseC(us);
			break;
		case Servo4A:
			Servo4.setPulseA(us);
			break;
		case Servo4B:
			Servo4.setPulseB(us);
			break;
		case Servo4C:
			Servo4.setPulseC(us);
			break;
		case Servo5A:
			Servo5.setPulseA(us);
			break;
		case Servo5B:
			Servo5.setPulseB(us);
			break;
		case Servo5C:
			Servo5.setPulseC(us);
			break;
		default:
			break;
	}
}

void PcbServo::enable(bool en /* = true */){
	switch(_servo){
		case Servo1A:
			en ? Servo1.EnableA() : Servo1.DisableA();
			break;
		case Servo1B:
			en ? Servo1.EnableB() : Servo1.DisableB();
			break;
		case Servo1C:
			en ? Servo1.EnableC() : Servo1.DisableC();
			break;
		case Servo3A:
			en ? Servo3.EnableA() : Servo3.DisableA();
			break;
		case Servo3B:
			en ? Servo3.EnableB() : Servo3.DisableB();
			break;
		case Servo3C:
			en ? Servo3.EnableC() : Servo3.DisableC();
			break;
		case Servo4A:
			en ? Servo4.EnableA() : Servo4.DisableA();
			break;
		case Servo4B:
			en ? Servo4.EnableB() : Servo4.DisableB();
			break;
		case Servo4C:
			en ? Servo4.EnableC() : Servo4.DisableC();
			break;
		case Servo5A:
			en ? Servo5.EnableA() : Servo5.DisableA();
			break;
		case Servo5B:
			en ? Servo5.EnableB() : Servo5.DisableB();
			break;
		case Servo5C:
			en ? Servo5.EnableC() : Servo5.DisableC();
			break;
		default:
			break;
	}
}