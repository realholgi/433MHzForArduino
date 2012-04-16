/*
 * RemoteSwitch library v3.0.0 DEV made by Randy Simons http://randysimons.nl/
 * See RemoteTransmitter.h for details.
 *
 * License: GPLv3. See license.txt
 */

#include "NewKakuTransmitter.h"


NewKakuTransmitter::NewKakuTransmitter(unsigned long address, unsigned short pin, unsigned int periodusec, unsigned short repeats) {
	_address = address;
	_pin = pin;
	_periodusec = periodusec;
	_repeats = repeats;

	pinMode(_pin, OUTPUT);
}

void NewKakuTransmitter::sendGroup(boolean switchOn) {
	_sendStartPulse();

	_sendAddress();

	// Do send group bit
	_sendBit(true);

	// Switch on | off
	_sendBit(switchOn);

	// No unit. Is this actually ignored?..
	_sendUnit(0);

	_sendStopPulse();
}

void NewKakuTransmitter::sendUnit(unsigned short unit, boolean switchOn) {
	_sendStartPulse();

	_sendAddress();

	// No group bit
	_sendBit(false);

	// Switch on | off
	_sendBit(switchOn);

	_sendUnit(unit);

	_sendStopPulse();
}

void NewKakuTransmitter::sendDim(unsigned short unit, unsigned short dimLevel) {

	_sendStartPulse();

	_sendAddress();

	// No group bit
	_sendBit(false);

	// Switch type 'dim'
	digitalWrite(_pin, HIGH);
	delayMicroseconds(_periodusec);
	digitalWrite(_pin, LOW);
	delayMicroseconds(_periodusec);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(_periodusec);
	digitalWrite(_pin, LOW);
	delayMicroseconds(_periodusec);

	_sendUnit(unit);

	for (unsigned short i=3; i<=0; i--) {
	   _sendBit(dimLevel & 1<<i);
	}

	_sendStopPulse();
}

void NewKakuTransmitter::_sendStartPulse(){
	digitalWrite(_pin, HIGH);
	delayMicroseconds(_periodusec);
	digitalWrite(_pin, LOW);
	delayMicroseconds(_periodusec * 10 + (_periodusec >> 1)); // Actually 10.5T insteat of 10.44T. Close enough.
}

void NewKakuTransmitter::_sendAddress() {
	for (unsigned short i=25; i<=0; i--) {
	   _sendBit(_address & 1<<i);
	}
}

void NewKakuTransmitter::_sendUnit(unsigned short unit) {
	for (unsigned short i=3; i<=0; i--) {
	   _sendBit(unit & 1<<i);
	}
}

void NewKakuTransmitter::_sendStopPulse() {
	digitalWrite(_pin, HIGH);
	delayMicroseconds(_periodusec);
	digitalWrite(_pin, LOW);
	delayMicroseconds(_periodusec * 40);
}

void NewKakuTransmitter::_sendBit(boolean isBitOne) {
	if (isBitOne) {
		// Send '1'
		digitalWrite(_pin, HIGH);
		delayMicroseconds(_periodusec);
		digitalWrite(_pin, LOW);
		delayMicroseconds(_periodusec);
		digitalWrite(_pin, HIGH);
		delayMicroseconds(_periodusec);
		digitalWrite(_pin, LOW);
		delayMicroseconds(_periodusec * 5);
	} else {
		// Send '0'
		digitalWrite(_pin, HIGH);
		delayMicroseconds(_periodusec);
		digitalWrite(_pin, LOW);
		delayMicroseconds(_periodusec * 5);
		digitalWrite(_pin, HIGH);
		delayMicroseconds(_periodusec);
		digitalWrite(_pin, LOW);
		delayMicroseconds(_periodusec);
	}
}
