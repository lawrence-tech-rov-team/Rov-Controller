/*
 * Spi.h
 *
 * Created: 2/19/2020 11:29:28 AM
 *  Author: zcarey
 */ 


#ifndef SPI_H_
#define SPI_H_


//#include <avr/io.h>
#include "../PinDefinitions/PCBPins.h"

#define SPI_CLOCK_DIV2 0x04 //4 is the x2 bit

class SPI{
public:
	static void begin(uint8_t clock = SPI_CLOCK_DIV2){
		//SPI_DIR |= SS;
		DDR_SPI |= MASK_MOSI | MASK_SCK | MASK_SS; //Not sure why, but SS pin requires to be set as output even when not being used.
		DDR_SPI &= ~(MASK_MISO);
		//disableCS();

		SPSR |= (clock >> 2);
		SPCR |= _BV(MSTR) | _BV(SPE) | (clock & 0x03);
	}

	static void end(){
		SPCR &= ~_BV(SPE);
	}

	//Write SPI assuming CS is low, meaning the device is selected.
	static void write8(uint8_t data){
		//enableCS();
		SPDR = data;
		asm volatile("nop");
		while(!(SPSR & _BV(SPIF)));
		//disableCS();
	}

	//write8, excepts also returns the received byte
	static uint8_t read_write8(uint8_t data){
		write8(data);
		return SPDR;
	}

	static void write16(uint16_t data){
		write8(data >> 8);
		write8(data);
	}

	static uint16_t read_write16(uint16_t data){
		uint16_t val;
		val |= read_write8(data >> 8);
		val = (val << 8) | read_write8(data);
		return val;
	}

	static void write(const void *buf, uint16_t nbyte){
		if(nbyte == 0) return;
		
		const uint8_t* buff = (const uint8_t*)(buf);
		SPDR = *buff;
		while(--nbyte){
			asm volatile("nop");
			while (!(SPSR & _BV(SPIF))) ;
			SPDR = *++buff;
		}
		asm volatile("nop");
		while (!(SPSR & _BV(SPIF))) ;
	}

	static void read_write(void *buf, uint16_t nbyte){
		if(nbyte == 0) return;
		
		uint8_t* buff = (uint8_t*)buf;
		SPDR = *buff;
		while(--nbyte){
			while(!(SPSR & _BV(SPIF)));
			*buff = SPDR;
			SPDR = *++buff;
		}
		while(!(SPSR & _BV(SPIF)));
	}
		
	static void read(void *buf, uint16_t nbyte, uint8_t dataSend = 0){
		if(nbyte == 0) return;
		
		uint8_t* buff = (uint8_t*)buf;
		while(nbyte--){
			SPDR = dataSend;
			//asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
			while(!(SPSR & _BV(SPIF)));
			*buff++ = SPDR;
		}
	}
		
private:
	/*inline static void enableCS(){
		SPI_PORT |= SS;
	}
	
	inline static void disableCS(){
		SPI_PORT &= ~SS;
	}*/
};

extern SPI SPI;


#endif /* SPI_H_ */