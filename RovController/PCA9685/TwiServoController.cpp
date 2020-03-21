/*
 * TwiServoController.cpp
 *
 * Created: 2/29/2020 10:16:01 PM
 *  Author: zcarey
 */ 

#include "TwiServoController.h"
#include "../Micro/CpuFreq.h"

TwiServoController::TwiServoController(const uint8_t addr) : controller(addr){
		
}

bool TwiServoController::begin(){
	controller.begin();
	// In theory the internal oscillator is 25MHz but it really isn't
	// that precise. You can 'calibrate' by tweaking this number till
	// you get the frequency you're expecting!
	controller.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz
	controller.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
	_delay_ms(10);
	return controller.getOscillatorFrequency() == 27000000;
}

void TwiServoController::setPulse(uint8_t num, uint16_t us){
	if(num < 16) controller.writeMicroseconds(num, us);
}

void TwiServoController::release(uint8_t num){
	if(num < 16) controller.setPWM(num, 0, 4096);
}

/*
void TwiServoController::sweep(){
	for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
		for(uint8_t i = 0; i < 16; i++){
			controller.setPWM(i, 0, pulselen);
		}
		_delay_ms(5);
	}
	_delay_ms(500);
	for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
		for(uint8_t i = 0; i < 16; i++){
			controller.setPWM(i, 0, pulselen);
		}
		_delay_ms(5);
	}
	_delay_ms(500);
}
*/
