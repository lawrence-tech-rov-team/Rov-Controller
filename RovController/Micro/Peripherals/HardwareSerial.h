/*
 * HardwareSerial.h
 *
 * Created: 3/20/2020 3:50:43 PM
 *  Author: zcarey
 */ 


#ifndef HARDWARESERIAL_H_
#define HARDWARESERIAL_H_

#include <inttypes.h>
#include "../../Utils/Stream.h"
#include "../CpuFreq.h"
#include "../Pins.h"

// Define config for Serial.begin(baud, config);
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

class HardwareSerial : public Stream {
protected:
	Register16* const _ubrr;
	Register* const _ucsra;
	Register* const _ucsrb;
	Register* const _ucsrc;
	Register* const _udr;

public:
	HardwareSerial(
		Register16 &ubrr,
		Register &ucsra, Register &ucsrb,
		Register &ucsrc, Register &udr
	);
	
	void begin(uint32_t baud, uint8_t config = SERIAL_8N1);
	void end();
	virtual int available(void);
	virtual int peek(void);
	virtual int read(void);
	virtual int availableForWrite(void);
	virtual void flush(void);
	virtual size_t write(uint8_t);
	inline size_t write(unsigned long n) { return write((uint8_t)n); }
	inline size_t write(long n) { return write((uint8_t)n); }
	inline size_t write(unsigned int n) { return write((uint8_t)n); }
	inline size_t write(int n) { return write((uint8_t)n); }
	using Print::write; // pull in write(str) and write(buf, size) from Print
	operator bool() { return true; }

	// Interrupt handlers - Not intended to be called externally
	inline void _rx_complete_irq(void);
	void _tx_udr_empty_irq(void);
};

#ifdef UBRR0
extern HardwareSerial Serial;
#endif

#ifdef UBRR1
extern HardwareSerial Serial1;
#endif

#ifdef UBRR2
extern HardwareSerial Serial2;
#endif

#ifdef UBRR3
extern HardwareSerial Serial3;
#endif

#endif /* HARDWARESERIAL_H_ */