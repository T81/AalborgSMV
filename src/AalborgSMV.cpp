/*************************************************************************
* AalborgSMV libary
* by T81 <tolis81@gmail.com> , September 03, 2014.
*
* This file is free software; you can redistribute it and/or modify
* it under the terms of either the GNU General Public License version 3
* published by the Free Software Foundation.
*************************************************************************/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <AalborgSMV.h>


/* Public functions
 * *******************************************************************************************
 * AalborgSMV()			library constructor
 * AalborgSMV(&dac)		instantiate a new library object and pass a DAC_MCP49xx reference 
 * begin(2,3,5)			set pins 2, 3 ,4 as the Direction, Closing and Purge pins respectively
 * speed(25)			opens the valve with 25% max speed. Negative values closes the valve
 * close()				valve set to full close overriding direction and speed
 * open()				valve set to full open overriding direction and speed
 * *******************************************************************************************
*/

AalborgSMV::AalborgSMV(DAC_MCP49xx* _DAC_MCP49xx) {
	_dac = _DAC_MCP49xx;
}

void AalborgSMV::begin(unsigned char directionPin, unsigned char closePin, unsigned char purgePin) {
	_directionPin = directionPin;
	_closePin = closePin;
	_purgePin = purgePin;
	pinMode(_directionPin, OUTPUT);
	pinMode(_closePin, OUTPUT);
	pinMode(_purgePin, OUTPUT);
}

void AalborgSMV::speed(float percentage) {
	_percentage = percentage;
	if (_percentage > 100) {
		_percentage = 100;
	}
	else if (_percentage < -100) {
		_percentage = -100;
	}
	if (_percentage != _previousPercentage) {
		_previousPercentage = _percentage;
		if (_percentage <= 0) {
			_percentage = abs(_percentage);
			setDirection(CLOSE);
		}
		else {
			setDirection(OPEN);
		}
		_dacBits = _percentage * 20.48;
		_dac->output(_dacBits);
	}
}

void AalborgSMV::close() {
	if (!_valveOverride[CLOSE]) {
		if (_valveOverride[PURGE]) {
			digitalWrite(_purgePin, LOW);
		}
		if (_previousPercentage) {
			_dac->output(0);
			_previousPercentage = 0;
		}
		_valveOverride[CLOSE] = true;
		digitalWrite(_closePin, HIGH);
	}
}

void AalborgSMV::purge() {
	if (!_valveOverride[PURGE]) {
		if (_valveOverride[CLOSE]) {
			digitalWrite(_closePin, LOW);
		}
		if (_previousPercentage) {
			_dac->output(0);
			_previousPercentage = 0;
		}
		_valveOverride[PURGE] = true;
		digitalWrite(_purgePin, HIGH);
	}
}

/* Private function
 * *******************************************************************************************
 * setDirection(bool direction)		function to choose either the opening or closing direction
 * *******************************************************************************************
*/
void AalborgSMV::setDirection(bool direction) {
	_direction = direction;
	if (_valveOverride[PURGE]) { 
		digitalWrite(_purgePin, LOW);
		_valveOverride[PURGE] = false;
	}
	if (_valveOverride[CLOSE]) { 
		digitalWrite(_closePin, LOW);
		_valveOverride[CLOSE] = false;
	}
	if (_previousDirection != _direction) {
		_previousDirection = _direction;
		digitalWrite(_directionPin, _direction);
	}
}
