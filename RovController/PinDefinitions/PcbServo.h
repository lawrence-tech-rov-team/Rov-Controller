/*
 * PcbServo.h
 *
 * Created: 3/16/2020 6:46:02 PM
 *  Author: zcarey
 */ 


#ifndef PCBSERVO_H_
#define PCBSERVO_H_

#include <inttypes.h>
#include <stdbool.h>

class PcbServo{
public:
	typedef enum {
		Servo1A,
		Servo1B,
		Servo1C,
		Servo3A,
		Servo3B,
		Servo3C,
		Servo4A,
		Servo4B,
		Servo4C,
		Servo5A,
		Servo5B,
		Servo5C
	} ServoId_t;

	PcbServo(ServoId_t servo);
	void begin();
	void setPulse(uint16_t us);
	void enable(bool en = true);
	inline void disable(){ enable(false); }

private:
	ServoId_t _servo;

};



#endif /* PCBSERVO_H_ */