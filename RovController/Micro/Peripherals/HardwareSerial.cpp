/*
 * HardwareSerial.cpp
 *
 * Created: 3/20/2020 3:51:09 PM
 *  Author: zcarey
 */ 

#include "HardwareSerial.h"
#include <avr/io.h>

HardwareSerial::HardwareSerial( Register16 &ubrr, Register &ucsra, Register &ucsrb, Register &ucsrc, Register &udr )
 : _ubrr(&ubrr), _ucsra(&ucsra), _ucsrb(&ucsrb), _ucsrc(&ucsrc), _udr(&udr)
{
}

void HardwareSerial::begin(uint32_t baud, uint8_t config /* = SERIAL_8N1 */){
	//Try u2x mode first
	uint16_t baud_setting = F_CPU / (8 * baud) - 1; //(F_CPU / 4 / baud - 1) / 2; 
	*_ucsra = _BV(U2X0);
	
	if(baud_setting > 4095){
		*_ucsra = 0;
		baud_setting = F_CPU / 16 * baud - 1; //(F_CPU / 8 / baud - 1) / 2; 
	}
	
	*_ubrr = baud_setting;
	*_ucsrc = config;
	
	sbi(*_ucsrb, RXEN0);
	sbi(*_ucsrb, TXEN0);
	//sbi(*_ucsrb, RXCIE0);
	//cbi(*_ucsrb, UDRIE0);
}

void HardwareSerial::end(){
	cbi(*_ucsrb, RXEN0);
	cbi(*_ucsrb, TXEN0);
	//cbi(*_ucsrb, RXCIE0);
	//cbi(*_ucsrb, UDRIE0);
}

int HardwareSerial::available(){
	return ((*_ucsra & _BV(RXC0)) > 0) ? 1 : 0;
}

int HardwareSerial::peek(){
	return -1;
}

int HardwareSerial::read(){
	while((*_ucsra & _BV(RXC0)) == 0) ;
	return *_udr;
}

int HardwareSerial::availableForWrite(){
	return ((*_ucsra & _BV(UDRE0)) > 0) ? 1 : 0;
}

void HardwareSerial::flush(){
	while ((*_ucsra & _BV(UDRE0)) == 0) ;
}

size_t HardwareSerial::write(uint8_t c){
	while ((*_ucsra & _BV(UDRE0)) == 0) ;
	*_udr = c;
	return 1;
}

#ifdef UBRR0
HardwareSerial Serial(UBRR0, UCSR0A, UCSR0B, UCSR0C, UDR0);
#endif

#ifdef UBRR1
HardwareSerial Serial1(UBRR1, UCSR1A, UCSR1B, UCSR1C, UDR1);
#endif

#ifdef UBRR2
HardwareSerial Serial2(UBRR2, UCSR2A, UCSR2B, UCSR2C, UDR2);
#endif

#ifdef UBRR3
HardwareSerial Serial3(UBRR3, UCSR3A, UCSR3B, UCSR3C, UDR3);
#endif
