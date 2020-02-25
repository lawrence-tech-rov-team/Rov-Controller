/*
 * TWI.h
 *
 * Created: 2/22/2020 10:40:27 PM
 *  Author: zcarey
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <inttypes.h>
//#include "../../Utils/Stream.h"
//#include <util/twi.h>

#ifndef TWI_FREQ
#define TWI_FREQ 100000L
#endif

//#ifndef TWI_BUFFER_LENGTH
//#define TWI_BUFFER_LENGTH 32
//#endif

//#ifndef TWI_BUFFER_LENGTH
//#define TWI_BUFFER_LENGTH 32
//#endif

#define TWI_READY 0
#define TWI_MRX   1
#define TWI_MTX   2
#define TWI_SRX   3
#define TWI_STX   4

class TWI/* : public Stream*/
{
private:
	//static uint8_t* rxBuffer;
	//static uint8_t rxBufferIndex;
	//static uint8_t rxBufferLength;

	//static uint8_t txAddress;
	//static uint8_t* txBuffer;
	//static uint8_t txBuffer[];
	//static uint8_t txBufferIndex;
	//static uint8_t txBufferLength;

	//static bool transmitting;
	//static void (*user_onRequest)(void);
	//static void (*user_onReceive)(uint8_t);
	//static void onRequestService(void);
	//static void onReceiveService(uint8_t*, int);
	//void beginTransmission(uint8_t);
	//uint8_t endTransmission(bool sendStop = true);

public:
	TWI();
	void begin();
	void begin(uint8_t);
	//void begin(int);
	void end();
	void setClock(uint32_t);
	bool readAsync(uint8_t* buffer, uint8_t address, uint8_t quantity, uint8_t* iaddress = 0, uint8_t ilen = 0, bool sendStop = true);
	bool writeAsync(uint8_t address, uint8_t* data, uint8_t len, uint8_t* iaddress = 0, uint8_t ilen = 0, bool sendStop = true);
	uint8_t getError();
	
	bool available();
	//uint8_t read(uint8_t* buffer);
	//uint8_t read(uint8_t* buffer, uint8_t maxLen);
/*
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *, size_t);
	virtual int peek(void);
	virtual void flush(void);
	*/
//	void onReceive( void (*)(int) );
//	void onRequest( void (*)(void) );

//	inline size_t write(unsigned long n) { return write((uint8_t)n); }
//	inline size_t write(long n) { return write((uint8_t)n); }
//	inline size_t write(unsigned int n) { return write((uint8_t)n); }
//	inline size_t write(int n) { return write((uint8_t)n); }*/
	//using Print::write;
};

extern TWI Twi;

#endif /* TWI_H_ */