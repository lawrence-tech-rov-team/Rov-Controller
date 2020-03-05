/*
 * Timer.h
 *
 * Created: 3/5/2020 9:52:41 AM
 *  Author: zcarey
 */ 


#ifndef HARDWARETIMER_H_
#define HARDWARETIMER_H_

#define USE_TIMER_0
#define USE_TIMER_2

#include "../PinDefinitions.h"

/*
	Due to some development time constraints, this timer class is designed for 20ms timing with a 16MHz clock.
*/
class HardwareTimer{
public:
	HardwareTimer(Register &tccrA, Register &tccrB, Register &timsk, Register &tcnt, Register &ocra);
	void begin();
	
	void start();
	bool finished();
	void waitForFinish();
	
	//NOT TO BE CALLED BY USER
	void isr_timer_comp();
private:
	Register* const _tccrA;
	Register* const _tccrB;
	Register* const _timsk;
	Register* const _tcnt;
	Register* const _ocra;
	
	uint8_t ovfRemaining;
};

#ifdef USE_TIMER_0
extern HardwareTimer Timer0;
#endif

#ifdef USE_TIMER_2
extern HardwareTimer Timer2;
#endif


#endif /* HARDWARETIMER_H_ */