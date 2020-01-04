/*
 * Print.h
 *
 * Created: 12/26/2019 3:39:12 PM
 *  Author: zcarey
 */ 


#ifndef PRINT_H_
#define PRINT_H_

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN
	#undef BIN
#endif
#define BIN 2

#include <inttypes.h>
#include <stdio.h> // for size_t
#include <string.h>

//#include "WString.h"
//#include "Printable.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <avr/pgmspace.h>
//#include <string.h>
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
*/

class Print{
private:
  //int write_error;
  uint8_t printNumber(uint32_t, uint8_t);
  uint8_t printFloat(double, uint8_t);
  
protected:
  //void setWriteError(int8_t err = 1) { write_error = err; }
	  
public:
  Print() {}//: write_error(0) {}
  
  //int getWriteError() { return write_error; }
  //void clearWriteError() { setWriteError(0); }
  
  virtual uint16_t write(uint8_t) = 0;
  uint16_t write(const char *str) {
	  if (str == NULL) return 0;
	  return write((const uint8_t *)str, strlen(str));
  }
  virtual uint16_t write(const uint8_t *buffer, uint16_t size);
  uint16_t write(const char *buffer, uint16_t size) {
	  return write((const uint8_t *)buffer, size);
  }

  // default to zero, meaning "a single write may block"
  // should be overriden by subclasses with buffering
  virtual int16_t availableForWrite() { return 0; }

  //uint16_t print(const __FlashStringHelper *);
  //uint16_t print(const String &);
  uint16_t print(const char[]);
  uint16_t print(char);
  uint16_t print(unsigned char, int = DEC);
  uint16_t print(int, int = DEC);
  uint16_t print(unsigned int, int = DEC);
  uint16_t print(long, int = DEC);
  uint16_t print(unsigned long, int = DEC);
  uint16_t print(double, int = 2);
  //uint16_t print(const Printable&);

  //uint16_t println(const __FlashStringHelper *);
  //uint16_t println(const String &s);
  uint16_t println(const char[]);
  uint16_t println(char);
  uint16_t println(unsigned char, int = DEC);
  uint16_t println(int, int = DEC);
  uint16_t println(unsigned int, int = DEC);
  uint16_t println(long, int = DEC);
  uint16_t println(unsigned long, int = DEC);
  uint16_t println(double, int = 2);
  //uint16_t println(const Printable&);
  uint16_t println(void);

  virtual void flush() { /* Empty implementation for backward compatibility */ }
};


#endif /* PRINT_H_ */