/*
 * Timer1.cpp
 *
 * Created: 1/15/2020 12:58:04 PM
 *  Author: zcarey
 */ 

#include "Timer1.h"

uint16_t Timer1::getTime(){
	return TCNT1;
}

void Timer1::reset(){
	TCNT1 = 0;
	TIFR1 |= _BV(TOV1);
}

void Timer1::begin(){
	TCCR1B |= _BV(CS10); //Enable timer, no prescale
}
