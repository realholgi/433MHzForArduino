/*
 * IntereruptChain library v1.0.0 made by Randy Simons http://randysimons.nl/
 *
 * License: GPLv3. See license.txt
 */

#include <InterruptChain.h>
     
void InterruptChainLink::init(InterruptCallback callbackIn, InterruptChainLink *nextIn) {
	callback = callbackIn;
	next = nextIn;
}

void InterruptChainLink::processInterrupt() {
	(callback)();
	if (next) {
		next->processInterrupt();
	}
}

InterruptChainLink *InterruptChain::chain[MAX_INTERRUPTS] = {NULL};
byte InterruptChain::mode = CHANGE;

void InterruptChain::setMode(byte modeIn) {     
    mode = modeIn;
}

void InterruptChain::addInterruptCallback(byte interruptNr, InterruptCallback callback) {
  InterruptChainLink *prevLink = chain[interruptNr]; // Note: the chain-array is NULL initialized, so the first time prevLink is indeed NULL
  
  chain[interruptNr] = (InterruptChainLink *) malloc(sizeof(InterruptChainLink)); // malloc instead of new, due to the lack of new / delete support in AVR-libc
  chain[interruptNr]->init(callback, prevLink);      
    
  switch (interruptNr) {
    case 0:
          attachInterrupt(0, InterruptChain::processInterrupt0, mode);
          break;
    case 1:
          attachInterrupt(1, InterruptChain::processInterrupt1, mode);
          break;
    case 2:
          attachInterrupt(2, InterruptChain::processInterrupt2, mode);
          break;
    case 3:
          attachInterrupt(3, InterruptChain::processInterrupt3, mode);
          break;
    case 4:
          attachInterrupt(4, InterruptChain::processInterrupt4, mode);
          break;
    case 5:
          attachInterrupt(5, InterruptChain::processInterrupt5, mode);
          break;
  }
}
    
void InterruptChain::processInterrupt0() {     
    chain[0]->processInterrupt();
}

void InterruptChain::processInterrupt1() {     
    chain[1]->processInterrupt();
}

void InterruptChain::processInterrupt2() {     
    chain[2]->processInterrupt();
}

void InterruptChain::processInterrupt3() {     
    chain[3]->processInterrupt();
}

void InterruptChain::processInterrupt4() {     
    chain[4]->processInterrupt();
}

void InterruptChain::processInterrupt5() {     
    chain[5]->processInterrupt();
}
