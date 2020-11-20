/*
 *  Interrupt and PWM utilities for 16 bit Timer3 on ATmega168/328
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *  Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
 *  Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
 *  Modified April 2012 by Paul Stoffregen - portable to other AVR chips, use inline functions
 *  Modified again, June 2014 by Paul Stoffregen - support Teensy 3.x & even more AVR chips
 *  Modified July 2017 by Stoyko Dimitrov - added support for ATTiny85 except for the PWM functionality
 *  
 *
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */

#ifndef TimerThree_h_
#define TimerThree_h_

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "config/known_16bit_timers.h"
#if defined (__AVR_ATtiny85__)
#define TIMER3_RESOLUTION 256UL  // Timer3 is 8 bit
#elif defined(__AVR__)
#define TIMER3_RESOLUTION 65536UL  // Timer3 is 16 bit
#else
#define TIMER3_RESOLUTION 65536UL  // assume 16 bits for non-AVR chips
#endif

// Placing nearly all the code in this .h file allows the functions to be
// inlined by the compiler.  In the very common case with constant values
// the compiler will perform all calculations and simply write constants
// to the hardware registers (for example, setPeriod).


class TimerThree
{

#if defined (__AVR_ATtiny85__)
  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
	TCCR3 = _BV(CTC3);              //clear timer1 when it matches the value in OCR3C
	TIMSK |= _BV(OCIE3A);           //enable interrupt when OCR3A matches the timer value
	setPeriod(microseconds);
    }
 //    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {		
	// const unsigned long cycles = microseconds * ratio;
	// if (cycles < TIMER3_RESOLUTION) {
	// 	clockSelectBits = _BV(CS10);
	// 	pwmPeriod = cycles;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 2UL) {
	// 	clockSelectBits = _BV(CS11);
	// 	pwmPeriod = cycles / 2;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 4UL) {
	// 	clockSelectBits = _BV(CS11) | _BV(CS10);
	// 	pwmPeriod = cycles / 4;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 8UL) {
	// 	clockSelectBits = _BV(CS12);
	// 	pwmPeriod = cycles / 8;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 16UL) {
	// 	clockSelectBits = _BV(CS12) | _BV(CS10);
	// 	pwmPeriod = cycles / 16;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 32UL) {
	// 	clockSelectBits = _BV(CS12) | _BV(CS11);
	// 	pwmPeriod = cycles / 32;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 64UL) {
	// 	clockSelectBits = _BV(CS12) | _BV(CS11) | _BV(CS10);
	// 	pwmPeriod = cycles / 64UL;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 128UL) {
	// 	clockSelectBits = _BV(CS13);
	// 	pwmPeriod = cycles / 128;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 256UL) {
	// 	clockSelectBits = _BV(CS13) | _BV(CS10);
	// 	pwmPeriod = cycles / 256;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 512UL) {
	// 	clockSelectBits = _BV(CS13) | _BV(CS11);
	// 	pwmPeriod = cycles / 512;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 1024UL) {
	// 	clockSelectBits = _BV(CS13) | _BV(CS11) | _BV(CS10);
	// 	pwmPeriod = cycles / 1024;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 2048UL) {
	// 	clockSelectBits = _BV(CS13) | _BV(CS12);
	// 	pwmPeriod = cycles / 2048;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 4096UL) {
	// 	clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS10);
	// 	pwmPeriod = cycles / 4096;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 8192UL) {
	// 	clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11);
	// 	pwmPeriod = cycles / 8192;
	// } else
	// if (cycles < TIMER3_RESOLUTION * 16384UL) {
	// 	clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11)  | _BV(CS10);
	// 	pwmPeriod = cycles / 16384;
	// } else {
	// 	clockSelectBits = _BV(CS13) | _BV(CS12) | _BV(CS11)  | _BV(CS10);
	// 	pwmPeriod = TIMER3_RESOLUTION - 1;
	// }
	// OCR3A = pwmPeriod;
	// OCR3C = pwmPeriod;
	// TCCR3 = _BV(CTC3) | clockSelectBits;
 //    }
	
 //    //****************************
 //    //  Run Control
 //    //****************************	
 //    void start() __attribute__((always_inline)) {
	// TCCR3 = 0;
	// TCNT3 = 0;		
	// resume();
 //    }
 //    void stop() __attribute__((always_inline)) {
	// TCCR3 = _BV(CTC3);
 //    }
 //    void restart() __attribute__((always_inline)) {
	// start();
 //    }
 //    void resume() __attribute__((always_inline)) {
	// TCCR3 = _BV(CTC3) | clockSelectBits;
 //    }
	
 //    //****************************
 //    //  PWM outputs
 //    //****************************
	// //Not implemented yet for ATTiny85
	// //TO DO
	
 //    //****************************
 //    //  Interrupt Function
 //    //****************************
 //    void attachInterrupt(void (*isr)()) __attribute__((always_inline)) {
	// isrCallback = isr;
	// TIMSK |= _BV(OCIE3A);
 //    }
 //    void attachInterrupt(void (*isr)(), unsigned long microseconds) __attribute__((always_inline)) {
	// if(microseconds > 0) setPeriod(microseconds);
	// attachInterrupt(isr);
 //    }
 //    void detachInterrupt() __attribute__((always_inline)) {
	// //TIMSK = 0; // Timer 0 and Timer 1 both use TIMSK register so setting it to 0 will override settings for Timer3 as well
	// TIMSK &= ~_BV(OCIE3A);
 //    }
 //    static void (*isrCallback)();
 //    static void isrDefaultUnused();

 //  private:
 //    static unsigned short pwmPeriod;
 //    static unsigned char clockSelectBits;
 //    static const byte ratio = (F_CPU)/ ( 1000000 );

#elif defined(__AVR__)      //This is the define we use for the camera project 
  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
	TCCR3B = _BV(WGM13);        // set mode as phase and frequency correct pwm, stop the timer
	TCCR3A = 0;                 // clear control register A 
	setPeriod(microseconds);
    }
    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {
	const unsigned long cycles = (F_CPU / 2000000) * microseconds;
	if (cycles < TIMER3_RESOLUTION) {
		clockSelectBits = _BV(CS10);
		pwmPeriod = cycles;
	} else
	if (cycles < TIMER3_RESOLUTION * 8) {
		clockSelectBits = _BV(CS11);
		pwmPeriod = cycles / 8;
	} else
	if (cycles < TIMER3_RESOLUTION * 64) {
		clockSelectBits = _BV(CS11) | _BV(CS10);
		pwmPeriod = cycles / 64;
	} else
	if (cycles < TIMER3_RESOLUTION * 256) {
		clockSelectBits = _BV(CS12);
		pwmPeriod = cycles / 256;
	} else
	if (cycles < TIMER3_RESOLUTION * 1024) {
		clockSelectBits = _BV(CS12) | _BV(CS10);
		pwmPeriod = cycles / 1024;
	} else {
		clockSelectBits = _BV(CS12) | _BV(CS10);
		pwmPeriod = TIMER3_RESOLUTION - 1;
	}
	ICR3 = pwmPeriod;
	TCCR3B = _BV(WGM13) | clockSelectBits;
    }

    //****************************
    //  Run Control
    //****************************
    void start() __attribute__((always_inline)) {
	TCCR3B = 0;
	TCNT3 = 0;		// TODO: does this cause an undesired interrupt?
	resume();
    }
    void stop() __attribute__((always_inline)) {
	TCCR3B = _BV(WGM13);
    }
    void restart() __attribute__((always_inline)) {
	start();
    }
    void resume() __attribute__((always_inline)) {
	TCCR3B = _BV(WGM13) | clockSelectBits;
    }

    //****************************
    //  PWM outputs
    //****************************
    void setPwmDuty(char pin, unsigned int duty) __attribute__((always_inline)) {
	unsigned long dutyCycle = pwmPeriod;
	dutyCycle *= duty;
	dutyCycle >>= 10;
	if (pin == TIMER3_A_PIN) OCR3A = dutyCycle;
	#ifdef TIMER3_B_PIN
	else if (pin == TIMER3_B_PIN) OCR3B = dutyCycle;
	#endif
	#ifdef TIMER3_C_PIN
	else if (pin == TIMER3_C_PIN) OCR3C = dutyCycle;
	#endif
    }
    void pwm(char pin, unsigned int duty) __attribute__((always_inline)) {
	if (pin == TIMER3_A_PIN) { pinMode(TIMER3_A_PIN, OUTPUT); TCCR3A |= _BV(COM3A1); }
	#ifdef TIMER3_B_PIN
	else if (pin == TIMER3_B_PIN) { pinMode(TIMER3_B_PIN, OUTPUT); TCCR3A |= _BV(COM3B1); }
	#endif
	#ifdef TIMER3_C_PIN
	else if (pin == TIMER3_C_PIN) { pinMode(TIMER3_C_PIN, OUTPUT); TCCR3A |= _BV(COM3C1); }
	#endif
	setPwmDuty(pin, duty);
	TCCR3B = _BV(WGM13) | clockSelectBits;
    }
    void pwm(char pin, unsigned int duty, unsigned long microseconds) __attribute__((always_inline)) {
	if (microseconds > 0) setPeriod(microseconds);
	pwm(pin, duty);
    }
    void disablePwm(char pin) __attribute__((always_inline)) {
	if (pin == TIMER3_A_PIN) TCCR3A &= ~_BV(COM3A1);
	#ifdef TIMER3_B_PIN
	else if (pin == TIMER3_B_PIN) TCCR3A &= ~_BV(COM3B1);
	#endif
	#ifdef TIMER3_C_PIN
	else if (pin == TIMER3_C_PIN) TCCR3A &= ~_BV(COM3C1);
	#endif
    }

    //****************************
    //  Interrupt Function
    //****************************
    void attachInterrupt(void (*isr)()) __attribute__((always_inline)) {
	isrCallback = isr;
	TIMSK3 = _BV(TOIE3);
    }
    void attachInterrupt(void (*isr)(), unsigned long microseconds) __attribute__((always_inline)) {
	if(microseconds > 0) setPeriod(microseconds);
	attachInterrupt(isr);
    }
    void detachInterrupt() __attribute__((always_inline)) {
	TIMSK3 = 0;
    }
    static void (*isrCallback)();
    static void isrDefaultUnused();

  private:
    // properties
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;




/*
#elif defined(__arm__) && defined(CORE_TEENSY)

#if defined(KINETISK)
#define F_TIMER F_BUS
#elif defined(KINETISL)
#define F_TIMER (F_PLL/2)
#endif

  public:
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned long microseconds=1000000) __attribute__((always_inline)) {
	setPeriod(microseconds);
    }
    void setPeriod(unsigned long microseconds) __attribute__((always_inline)) {
	const unsigned long cycles = (F_TIMER / 2000000) * microseconds;
  // A much faster if-else
  // This is like a binary serch tree and no more than 3 conditions are evaluated.
  // I haven't checked if this becomes significantly longer ASM than the simple ladder.
  // It looks very similar to the ladder tho: same # of if's and else's
 
  /*
  // This code does not work properly in all cases :(
  // https://github.com/PaulStoffregen/TimerThree/issues/17 
  if (cycles < TIMER3_RESOLUTION * 16) {
    if (cycles < TIMER3_RESOLUTION * 4) {
      if (cycles < TIMER3_RESOLUTION) {
        clockSelectBits = 0;
        pwmPeriod = cycles;
      }else{
        clockSelectBits = 1;
        pwmPeriod = cycles >> 1;
      }
    }else{
      if (cycles < TIMER3_RESOLUTION * 8) {
        clockSelectBits = 3;
        pwmPeriod = cycles >> 3;
      }else{
        clockSelectBits = 4;
        pwmPeriod = cycles >> 4;
      }
    }
  }else{
    if (cycles > TIMER3_RESOLUTION * 64) {
      if (cycles > TIMER3_RESOLUTION * 128) {
        clockSelectBits = 7;
        pwmPeriod = TIMER3_RESOLUTION - 1;
      }else{
        clockSelectBits = 7;
        pwmPeriod = cycles >> 7;
      }
    }
    else{
      if (cycles > TIMER3_RESOLUTION * 32) {
        clockSelectBits = 6;
        pwmPeriod = cycles >> 6;
      }else{
        clockSelectBits = 5;
        pwmPeriod = cycles >> 5;
      }
    }
  }
  *//*
	if (cycles < TIMER3_RESOLUTION) {
		clockSelectBits = 0;
		pwmPeriod = cycles;
	} else
	if (cycles < TIMER3_RESOLUTION * 2) {
		clockSelectBits = 1;
		pwmPeriod = cycles >> 1;
	} else
	if (cycles < TIMER3_RESOLUTION * 4) {
		clockSelectBits = 2;
		pwmPeriod = cycles >> 2;
	} else
	if (cycles < TIMER3_RESOLUTION * 8) {
		clockSelectBits = 3;
		pwmPeriod = cycles >> 3;
	} else
	if (cycles < TIMER3_RESOLUTION * 16) {
		clockSelectBits = 4;
		pwmPeriod = cycles >> 4;
	} else
	if (cycles < TIMER3_RESOLUTION * 32) {
		clockSelectBits = 5;
		pwmPeriod = cycles >> 5;
	} else
	if (cycles < TIMER3_RESOLUTION * 64) {
		clockSelectBits = 6;
		pwmPeriod = cycles >> 6;
	} else
	if (cycles < TIMER3_RESOLUTION * 128) {
		clockSelectBits = 7;
		pwmPeriod = cycles >> 7;
	} else {
		clockSelectBits = 7;
		pwmPeriod = TIMER3_RESOLUTION - 1;
	}

	uint32_t sc = FTM1_SC;
	FTM1_SC = 0;
	FTM1_MOD = pwmPeriod;
	FTM1_SC = FTM_SC_CLKS(1) | FTM_SC_CPWMS | clockSelectBits | (sc & FTM_SC_TOIE);
    }

    //****************************
    //  Run Control
    //****************************
    void start() __attribute__((always_inline)) {
	stop();
	FTM1_CNT = 0;
	resume();
    }
    void stop() __attribute__((always_inline)) {
	FTM1_SC = FTM1_SC & (FTM_SC_TOIE | FTM_SC_CPWMS | FTM_SC_PS(7));
    }
    void restart() __attribute__((always_inline)) {
	start();
    }
    void resume() __attribute__((always_inline)) {
	FTM1_SC = (FTM1_SC & (FTM_SC_TOIE | FTM_SC_PS(7))) | FTM_SC_CPWMS | FTM_SC_CLKS(1);
    }

    //****************************
    //  PWM outputs
    //****************************
    void setPwmDuty(char pin, unsigned int duty) __attribute__((always_inline)) {
	unsigned long dutyCycle = pwmPeriod;
	dutyCycle *= duty;
	dutyCycle >>= 10;
	if (pin == TIMER3_A_PIN) {
		FTM1_C0V = dutyCycle;
	} else if (pin == TIMER3_B_PIN) {
		FTM1_C1V = dutyCycle;
	}
    }
    void pwm(char pin, unsigned int duty) __attribute__((always_inline)) {
	setPwmDuty(pin, duty);
	if (pin == TIMER3_A_PIN) {
		*portConfigRegister(TIMER3_A_PIN) = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE;
	} else if (pin == TIMER3_B_PIN) {
		*portConfigRegister(TIMER3_B_PIN) = PORT_PCR_MUX(3) | PORT_PCR_DSE | PORT_PCR_SRE;
	}
    }
    void pwm(char pin, unsigned int duty, unsigned long microseconds) __attribute__((always_inline)) {
	if (microseconds > 0) setPeriod(microseconds);
	pwm(pin, duty);
    }
    void disablePwm(char pin) __attribute__((always_inline)) {
	if (pin == TIMER3_A_PIN) {
		*portConfigRegister(TIMER3_A_PIN) = 0;
	} else if (pin == TIMER3_B_PIN) {
		*portConfigRegister(TIMER3_B_PIN) = 0;
	}
    }

    //****************************
    //  Interrupt Function
    //****************************
    void attachInterrupt(void (*isr)()) __attribute__((always_inline)) {
	isrCallback = isr;
	FTM1_SC |= FTM_SC_TOIE;
	NVIC_ENABLE_IRQ(IRQ_FTM1);
    }
    void attachInterrupt(void (*isr)(), unsigned long microseconds) __attribute__((always_inline)) {
	if(microseconds > 0) setPeriod(microseconds);
	attachInterrupt(isr);
    }
    void detachInterrupt() __attribute__((always_inline)) {
	FTM1_SC &= ~FTM_SC_TOIE;
	NVIC_DISABLE_IRQ(IRQ_FTM1);
    }
    static void (*isrCallback)();
    static void isrDefaultUnused();

  private:
    // properties
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;

#undef F_TIMER
*/
#endif
};

extern TimerThree Timer3;

#endif

