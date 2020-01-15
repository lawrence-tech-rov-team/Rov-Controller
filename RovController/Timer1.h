/*
 * Timer1.h
 *
 * Created: 1/15/2020 12:57:55 PM
 *  Author: zcarey
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/io.h>

class Timer1{
public:
	static uint16_t getTime();
	static void reset();
	static void begin();

private:	
};

#endif /* TIMER1_H_ */