/*
 * Print.cpp
 *
 * Created: 12/26/2019 3:39:31 PM
 *  Author: zcarey
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "Arduino.h"

#include "Print.h"

// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */
uint16_t Print::write(const uint8_t *buffer, uint16_t size)
{
  uint16_t n = 0;
  while (size--) {
    if (write(*buffer++)) n++;
    else break;
  }
  return n;
}
/*
uint16_t Print::print(const __FlashStringHelper *ifsh)
{
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  uint16_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    if (write(c)) n++;
    else break;
  }
  return n;
}
*/
/*
uint16_t Print::print(const String &s)
{
  return write(s.c_str(), s.length());
}
*/
uint16_t Print::print(const char str[])
{
  return write(str);
}

uint16_t Print::print(char c)
{
  return write(c);
}

uint16_t Print::print(unsigned char b, int base)
{
  return print((unsigned long) b, base);
}

uint16_t Print::print(int n, int base)
{
  return print((long) n, base);
}

uint16_t Print::print(unsigned int n, int base)
{
  return print((unsigned long) n, base);
}

uint16_t Print::print(long n, int base)
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

uint16_t Print::print(unsigned long n, int base)
{
  if (base == 0) return write(n);
  else return printNumber(n, base);
}

uint16_t Print::print(double n, int digits)
{
  return printFloat(n, digits);
}
/*
uint16_t Print::println(const __FlashStringHelper *ifsh)
{
  uint16_t n = print(ifsh);
  n += println();
  return n;
}
*/
/*
uint16_t Print::print(const Printable& x)
{
  return x.printTo(*this);
}
*/
uint16_t Print::println(void)
{
  return write("\r\n");
}
/*
uint16_t Print::println(const String &s)
{
  uint16_t n = print(s);
  n += println();
  return n;
}
*/
uint16_t Print::println(const char c[])
{
  uint16_t n = print(c);
  n += println();
  return n;
}

uint16_t Print::println(char c)
{
  uint16_t n = print(c);
  n += println();
  return n;
}

uint16_t Print::println(unsigned char b, int base)
{
  uint16_t n = print(b, base);
  n += println();
  return n;
}

uint16_t Print::println(int num, int base)
{
  uint16_t n = print(num, base);
  n += println();
  return n;
}

uint16_t Print::println(unsigned int num, int base)
{
  uint16_t n = print(num, base);
  n += println();
  return n;
}

uint16_t Print::println(long num, int base)
{
  uint16_t n = print(num, base);
  n += println();
  return n;
}

uint16_t Print::println(unsigned long num, int base)
{
  uint16_t n = print(num, base);
  n += println();
  return n;
}

uint16_t Print::println(double num, int digits)
{
  uint16_t n = print(num, digits);
  n += println();
  return n;
}
/*
uint16_t Print::println(const Printable& x)
{
  uint16_t n = print(x);
  n += println();
  return n;
}
*/
// Private Methods /////////////////////////////////////////////////////////////

uint8_t Print::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return write(str);
}

uint8_t Print::printFloat(double number, uint8_t digits) 
{ 
  uint16_t n = 0;
  
  if (isnan(number)) return print("nan");
  if (isinf(number)) return print("inf");
  if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     n += print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print('.'); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    n += print(toPrint);
    remainder -= toPrint; 
  } 
  
  return n;
}
