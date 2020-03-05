/*
 * HardwareTimer.cpp
 *
 * Created: 3/5/2020 9:57:11 AM
 *  Author: zcarey
 */ 

#include "HardwareTimer.h"
#include <avr/interrupt.h>

#define CLK_DISABLE (0)
#define CLK_DIV_1 (_BV(CS00))
#define CLK_DIV_8 (_BV(CS01))
#define CLK_DIV_64 (_BV(CS01) | _BV(CS00))
#define CLK_DIV_256 (_BV(CS02))
#define CLK_DIV_1024 (_BV(CS02) | _BV(CS00))

HardwareTimer::HardwareTimer(Register &tccrA, Register &tccrB, Register &timsk, Register &tcnt, Register &ocra)
: _tccrA(&tccrA), _tccrB(&tccrB), _timsk(&timsk), _tcnt(&tcnt), _ocra(&ocra)
{
	
}

void HardwareTimer::begin(){
	*_tccrA = _BV(WGM01); //Normal mode, off by default
	*_tccrB = 0;
	*_timsk = _BV(OCIE0A); //Overflow interrupt
	*_ocra = 155; //Clock div 1024 ~= 10ms per overflow
	sei();
}//OCR0A

void HardwareTimer::start(){
	*_tccrB = 0; //Disable timer
	ovfRemaining = 2;
	*_tcnt = 0; //Reset timer
	*_tccrB = CLK_DIV_1024; 
}

bool HardwareTimer::finished(){
	return ovfRemaining == 0;
}

void HardwareTimer::waitForFinish(){
	while(ovfRemaining != 0){
	}
}

void HardwareTimer::isr_timer_comp(){
	if(ovfRemaining > 0) ovfRemaining--;
}

#ifdef USE_TIMER_0
HardwareTimer Timer0(TCCR0A, TCCR0B, TIMSK0, TCNT0, OCR0A);

ISR(TIMER0_COMPA_vect){
	Timer0.isr_timer_comp();
}
#endif

#ifdef USE_TIMER_2
HardwareTimer Timer2(TCCR2A, TCCR2B, TIMSK2, TCNT2, OCR2A);

ISR(TIMER2_COMPA_vect){
	Timer2.isr_timer_comp();
}
#endif


