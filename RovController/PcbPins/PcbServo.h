/*
 * PcbServo.h
 *
 * Created: 3/20/2020 7:20:23 PM
 *  Author: zcarey
 */ 


#ifndef PCBSERVO_H_
#define PCBSERVO_H_


#include <inttypes.h>
#include <stdbool.h>

class PcbServo{
	public:
	//PcbServo(ServoId_t servo);
	//void begin();
	virtual void setPulse(uint16_t us) = 0;
	virtual void enable(bool en = true) = 0;
	inline void disable(){ enable(false); }

	protected:
	PcbServo(){ }

	private:
	//ServoId_t _servo;

};


#endif /* PCBSERVO_H_ */