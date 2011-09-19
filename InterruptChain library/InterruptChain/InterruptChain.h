/*
 * IntereruptChain library v1.0.0
 *
 * Copyright 2011 by Randy Simons http://randysimons.nl/
 *
 * License: GPLv3. See license.txt
 */

#ifndef InterruptChain_h
#define InterruptChain_h

#include "WProgram.h"

// Arduino Mega has 6 interrupts. For smaller Arduinos and / or to save a few bytes memory you can lower it to 2 or even 1. Don't go higher than 6 tho.
#define MAX_INTERRUPTS 6

typedef void (*InterruptCallback)();

/**
 * For internal use
 */
class InterruptChainLink {
	private:
		InterruptChainLink *next;
		InterruptCallback callback;

	public:
		void init(InterruptCallback callbackIn, InterruptChainLink *nextIn);

		void processInterrupt();    
};

class InterruptChain {  
	public:
		/**
		 * Add an interrupt handler on interrupt interruptNr. The callback is of the same type as
		 * Arduino's standard attachInterrupt().
		 *
		 * So, instead of attachInterrupt(0, callback, CHANGE); you can use
		 * InterruptChain::addInterruptCallback(0, callback);
		 * 
		 * You can add more than one callback to a single interrupt! The callbacks are called in 
		 * the reversed order in which they were added.
		 */
		static void addInterruptCallback(byte interruptNr, InterruptCallback callbackIn);
		
		/**
		 * Set the interrupt mode. By default the interrupt mode is CHANGE. If you need this changed,
		 * call setMode before adding interrupt handlers.
		 *
		 * @param modeIn LOW, CHANGE, RISING or FALLING
		 */
		static void setMode(byte modeIn);
	
	private:
		static byte mode;

		static InterruptChainLink *chain[6];

		static void processInterrupt0();

		static void processInterrupt1();

		static void processInterrupt2();

		static void processInterrupt3();

		static void processInterrupt4();

		static void processInterrupt5();
};

#endif
