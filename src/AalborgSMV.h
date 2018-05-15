/*************************************************************************
* AalborgSMV libary
* by T81 <tolis81@gmail.com> , September 03, 2014.
*
* This file is free software; you can redistribute it and/or modify
* it under the terms of either the GNU General Public License version 3
* published by the Free Software Foundation.
*************************************************************************/

#ifndef AalborgSMV_h
#define AalborgSMV_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <DAC_MCP49xx.h>	// DAC library

#define CLOSE 0
#define OPEN 1
#define PURGE 1

class AalborgSMV {
	public:
		AalborgSMV(DAC_MCP49xx*);
		void begin(unsigned char directionPin, unsigned char closePin, unsigned char purgePin);
		void speed(float percentage);
		void close();
		void purge();
	
	private:
		unsigned char _directionPin, _closePin, _purgePin;
		unsigned int _dacBits;
		float _percentage, _previousPercentage;
		bool _direction, _previousDirection;
		bool _valveOverride[2];
		DAC_MCP49xx* _dac;
		void setDirection(bool direction);
};
#endif
