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

/*
 * Simple Stepper class.
 */
class SimpleStepper {
public:
    volatile long ticksRemaining;   // remaining ticks, 2 ticks = 1 pulse = 1 microstep/step
        
    //Une variable pour chaque moteur qui contient le nombre de pas qu'il a effectué : stepper.actuStep Cela nous fourni l'information de position
    //Une variable pour la vitesse actuelle de chaque moteur stepper.actuPeriod
    //Une variable pour la vitesse cible de chaque moteur stepper.tagetPeriod
    //Une variable pour la prochaine vitesse de chaque moteur stepper.nextPeriod
    //Une variable pour le delta période du timer de chaque moteur stepper.deltaPeriod
    int actuStep;
    _Bool actuDir;
    int deltaStep;
    int actuPeriod;
    int targetPeriod;
    int nextPeriod;
    int deltaPeriod;
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
    static void ticking1();
    static void ticking2();
    static void ticking3();
    static void ticking4();
    
private:
    static SimpleStepper *firstInstance;
    static SimpleStepper *secondInstance;
    static SimpleStepper *thirdInstance;
    static SimpleStepper *fourthInstance;
    static int tickRefresh;
};

#endif // SIMPLE_STEPPER_BASE_H