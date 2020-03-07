/*
 * HardwareTimer.cpp
 *
 * Created: 3/5/2020 9:57:11 AM
 *  Author: zcarey
 */ 

#include "HardwareTimer.h"
#include "../Utils/CpuFreq.h"
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
/*
inline uint16_t divRoundUp(uint16_t n, uint16_t d){
	return ((n - 1) / d) + 1;
}
*/
float HardwareTimer::findPrescale(float ms){
	float prescale = (ms * (F_CPU / 1000.0)) / 256.0;
	
	if(prescale <= 1.0){
		prescaleMask = CLK_DIV_1;
		return 1.0;
	}else if(prescale <= 8.0){
		prescaleMask = CLK_DIV_8;
		return 8.0;
	}else if(prescale <= 64.0){
		prescaleMask = CLK_DIV_64;
		return 64.0;
	}else if(prescale <= 256.0){
		prescaleMask = CLK_DIV_256;
		return 256.0;
	}else{ //if(prescale <= 1024) return 1024;
		prescaleMask = CLK_DIV_1024;
		return 1024.0;	
	}
}

void HardwareTimer::beginMs(float ms){
	*_tccrA = _BV(WGM01); //CTC mode, off by default
	*_tccrB = 0;
	*_timsk = _BV(OCIE0A); //Overflow interrupt
	sei();
	
	float P = findPrescale(ms);
	float TOP = ((ms * F_CPU) / (1000.0 * P)) - 1;
	if(TOP > 255.0){
		*_ocra = 255;
	}else if (TOP < 0){
		*_ocra = 0;
	}else{
		*_ocra = (uint8_t)(TOP + 0.5);
	}
}

void HardwareTimer::beginUs(float us){
	beginMs(us / 1000.0);
}

void HardwareTimer::beginNs(float ns){
	beginMs(ns / 1000000.0);
}

void HardwareTimer::start(uint8_t ticks/*= 1*/){
	*_tccrB = 0; //Disable timer
	ovfRemaining = ticks;
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


