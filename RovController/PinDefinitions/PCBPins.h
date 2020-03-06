/*
 * PCBPins.h
 *
 * Created: 3/5/2020 10:54:03 AM
 *  Author: zcarey
 */ 


#ifndef PCBPINS_H_
#define PCBPINS_H_

#include "ArduinoPins.h"

#include "PCB_V1.h"
//#include "PCB_V3.h"

#define DDR_MISCA DDRA
#define PORT_MISCA PORTA
#define PIN_MISCA PORTA
#define MASK_MISCA24 _BV(PA2)
#define MASK_MISCA26 _BV(PA4)
#define MASK_MISCA28 _BV(PA6)

#define DDR_MISCB DDRC
#define PORT_MISCB PORTC
#define PIN_MISCB PINC
#define MASK_MISCB30 _BV(PC7)
#define MASK_MISCB32 _BV(PC5)
#define MASK_MISCB34 _BV(PC3)

#endif /* PCBPINS_H_ */