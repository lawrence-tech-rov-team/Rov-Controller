/*
 * Wire.h
 *
 * Created: 2/23/2020 11:57:26 AM
 *  Author: zcarey
 */ 


#ifndef WIRE_H_
#define WIRE_H_


#include <inttypes.h>
#include "../../Utils/Stream.h"
//#include <util/twi.h>

#ifndef TWI_FREQ
#define TWI_FREQ 100000L
#endif

#ifndef TWI_BUFFER_LENGTH
#define TWI_BUFFER_LENGTH 32
#endif

#ifndef TWI_BUFFER_LENGTH
#define TWI_BUFFER_LENGTH 32
#endif

#define TWI_READY 0
#define TWI_MRX   1
#define TWI_MTX   2
#define TWI_SRX   3
#define TWI_STX   4

class TwoWire : public Stream
{
	private:
	static uint8_t rxBuffer[];
	static uint8_t rxBufferIndex;
	static uint8_t rxBufferLength;

	static uint8_t txAddress;
	static uint8_t txBuffer[];
	static uint8_t txBufferIndex;
	static uint8_t txBufferLength;

	static bool transmitting;
	static void (*user_onRequest)(void);
	static void (*user_onReceive)(int);
	static void onRequestService(void);
	static void onReceiveService(uint8_t*, int);

	public:
	TwoWire();
	void begin();
	void begin(uint8_t);
	void begin(int);
	void end();
	void setClock(uint32_t);
	void beginTransmission(uint8_t);
	void beginTransmission(int);
	uint8_t endTransmission(void);
	uint8_t endTransmission(uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
	uint8_t requestFrom(int, int);
	uint8_t requestFrom(int, int, int);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *, size_t);
	virtual int available(void);
	virtual int read(void);
	virtual int peek(void);
	virtual void flush(void);
	void onReceive( void (*)(int) );
	void onRequest( void (*)(void) );

	inline size_t write(unsigned long n) { return write((uint8_t)n); }
	inline size_t write(long n) { return write((uint8_t)n); }
	inline size_t write(unsigned int n) { return write((uint8_t)n); }
	inline size_t write(int n) { return write((uint8_t)n); }
	using Print::write;
};

extern TwoWire Wire;


#endif /* WIRE_H_ */