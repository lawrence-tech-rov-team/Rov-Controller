/*
 * PCA9685.h
 *
 * Created: 2/29/2020 10:37:57 PM
 *  Author: zcarey
 */ 


#ifndef PCA9685_H_
#define PCA9685_H_


#include <inttypes.h>

class PCA9685{
public:
	PCA9685(const uint8_t addr);
	
	void begin(uint8_t prescale = 0);
	void reset();
	void sleep();
	void wakeup();
	void setExtClk(uint8_t prescale);
	void setPWMFreq(float freq);
	void setOutputMode(bool totempole);
	uint8_t getPWM(uint8_t num);
	void setPWM(uint8_t num, uint16_t on, uint16_t off);
	void setPin(uint8_t num, uint16_t val, bool invert = false);
	uint8_t readPrescale(void);
	void writeMicroseconds(uint8_t num, uint16_t Microseconds);

	void setOscillatorFrequency(uint32_t freq);
	uint32_t getOscillatorFrequency(void);

private:
	const uint8_t _addr;
	uint32_t _oscillator_freq;
	uint8_t _prescale;
	
	uint8_t read8(uint8_t addr);
	void write8(uint8_t addr, uint8_t d);
};


#endif /* PCA9685_H_ */