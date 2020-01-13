/*
 * Robot.cpp
 *
 * Created: 1/4/2020 3:41:02 PM
 *  Author: zcarey
 */ 

#include "Robot.h"

bool Robot::begin(){
	LedDDR |= LedPin;
	
	return true;
}

void Robot::SetLed(bool illuminate){
	if(illuminate) LedPort |= LedPin;
	else LedPort &= ~LedPin;
}
