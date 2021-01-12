/**
    @file SimpleStepper.h
    @author Evert Chin
    @brief Fast and Simple Stepper Driver
    
   * This file may be redistributed under the terms of the MIT license.
   * A copy of this license has been included with this distribution in the file LICENSE.
   */
#ifndef SIMPLE_STEPPER_BASE_H
#define SIMPLE_STEPPER_BASE_H

#include <Arduino.h>
#include "Pin.h"
#include "Global.h"
#include "TimerOne.h"
#include "TimerThree.h"
#include "TimerFour.h"
#include "TimerFive.h"

/*
 * Simple Stepper class.
 */
class SimpleStepper {
public:
    volatile long ticksRemaining;   // remaining ticks, 2 ticks = 1 pulse = 1 microstep/step
    volatile static int tickRefresh;//Number of ticks remaining before compute a new speed
    long actuSteps;
    long deltaStep;
    _Bool actuDir;  //0 = ANTICW, 1 = CLOCKWISE
    long actuPeriod;
    long targetPeriod;
    //long nextPeriod; //Enlevée récemment, tester si tout fonctionne bien avant de l'enlever définitivement mais à priori derait pas poser soucis
    long deltaPeriod;
    _Bool isRef;

protected:
    /* for some stupid reason the Pin class requires initialization */ 
    Pin dirPin = Pin(1000);
    Pin stepPin = dirPin;
    bool paused;
    uint8_t stepperTimer;
    
public:
    SimpleStepper(uint8_t dirpin, uint8_t steppin, uint8_t stepperTimer);
    void init();
    void setPulse(long pulse);
    bool step(long steps, uint8_t direction);
    bool step(long steps, uint8_t direction, long pulse);
    long getRemainingSteps();
    long stop();
    void pause();
    void resume();
    bool isStepping();
    bool isStopped();
    bool isPaused();

    static int getTickRefresh();
    static int setTickRefresh(int setValue);
    static void ticking1();
    static void ticking2();
    static void ticking3();
    static void ticking4();
    
private:
    static SimpleStepper *firstInstance;
    static SimpleStepper *secondInstance;
    static SimpleStepper *thirdInstance;
    static SimpleStepper *fourthInstance;
    
};

#endif // SIMPLE_STEPPER_BASE_H
