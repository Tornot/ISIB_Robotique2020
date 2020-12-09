/*
 *  Interrupt and PWM utilities for 16 bit Timer5 on ATmega168/328
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *  Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
 *  Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
 *  Modified Oct 2009 by Dan Clemens to work with Timer5 of the ATMega1280 or Arduino Mega
 *  Modified April 2012 by Paul Stoffregen
 *  Modified again, June 2014 by Paul Stoffregen
 *  Modified July 2017 by Stoyko Dimitrov - added support for ATTiny85 except for the PWM functionality
 *
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */

#include "TimerFive.h"

TimerFive Timer5;              // preinstatiate

unsigned short TimerFive::pwmPeriod = 0;
unsigned char TimerFive::clockSelectBits = 0;
void (*TimerFive::isrCallback)() = TimerFive::isrDefaultUnused;

// interrupt service routine that wraps a user defined function supplied by attachInterrupt
#if defined (__AVR_ATtiny85__)
ISR(Timer5_COMPA_vect)
{
  Timer5.isrCallback();
}
#elif defined(__AVR__)
ISR(TIMER5_OVF_vect)
{
  Timer5.isrCallback();
}

#endif

void TimerFive::isrDefaultUnused()
{
}