/*
 * HardwareServo.h
 *
 * Created: 2/29/2020 11:14:40 AM
 *  Author: zcarey
 */ 


#ifndef HARDWARESERVO_H_
#define HARDWARESERVO_H_

#include "../PinDefinitions/PCBPins.h"

class HardwareServo {
private:
	Register16* const _icr;
	Register* const _tccrA;
	Register* const _tccrB;
	Register16* const _ocrA;
	Register16* const _ocrB;
	Register16* const _ocrC;
	
	Register* const _DDR;
	Register* const _PORT;
	
	const uint8_t _PINA;
	const uint8_t _PINB;
	const uint8_t _PINC; 
	
	uint16_t _minA;
	uint16_t _minB;
	uint16_t _minC;
	
	uint16_t _maxA;
	uint16_t _maxB;
	uint16_t _maxC;
	
public:
	HardwareServo(Register16 &icr, Register &tccrA, Register &tccrB, Register16 &ocrA, Register16 &ocrB, Register16 &ocrC, Register &ddr, Register &port, const uint8_t pinA, const uint8_t pinB, const uint8_t pinC);
	
	void begin();
	void end();
	
	void EnableA();
	void EnableB();
	void EnableC();
	
	void DisableA();
	void DisableB();
	void DisableC();
	
	void setPulseA(uint8_t pulse);
	void setPulseB(uint8_t pulse);
	void setPulseC(uint8_t pulse);

	void setMinA(uint16_t us);
	void setMinB(uint16_t us);
	void setMinC(uint16_t us);
	
	void setMaxA(uint16_t us);
	void setMaxB(uint16_t us);
	void setMaxC(uint16_t us);
};

extern HardwareServo Servo1;
extern HardwareServo Servo3;
extern HardwareServo Servo4;
extern HardwareServo Servo5;

#endif /* HARDWARESERVO_H_ */