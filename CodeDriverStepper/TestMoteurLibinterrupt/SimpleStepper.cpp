/**
    @file SimpleStepper.cpp
    @author Evert Chin
    @brief Fast and Simple Stepper Driver

   * This file may be redistributed under the terms of the MIT license.
   * A copy of this license has been included with this distribution in the file LICENSE.
   */

#include "SimpleStepper.h"
#include "TimerOne.h"
#include "TimerThree.h"

SimpleStepper *SimpleStepper::firstInstance;
SimpleStepper *SimpleStepper::secondInstance;

SimpleStepper::SimpleStepper(uint8_t dirpin, uint8_t steppin, uint8_t stepperTimer){
    switch (stepperTimer)
    {
        case 1:
            firstInstance = this;
            break;
        case 3:
            secondInstance = this;
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
    this->dirPin = Pin(dirpin);
    this->stepPin = Pin(steppin);
    this->stepperTimer = stepperTimer;
}

void SimpleStepper::init(){     //Utiliser un tableau de timer pour accéder à celui que l'on veut. (du coup on évite le switch case) tabTimer[1].initalize()
    dirPin.setOutput();
    stepPin.setOutput();

    switch (this->stepperTimer)
    {
        case 1:
            Serial.print("firstInstance of stepper with stepperTimer : ");
            Serial.print(this->stepperTimer);
            Serial.println(" is : ");
            //Serial.println(this->firstInstance);
            Timer1.initialize();
            Timer1.attachInterrupt(SimpleStepper::ticking1); 
            Timer1.stop();
            break;
        case 3:
            Serial.print("secondInstance of stepper with stepperTimer : ");
            Serial.print(this->stepperTimer);
            Serial.println(" is : ");
            //Serial.println(this->seconInstance);
            Timer3.initialize();
            Timer3.attachInterrupt(SimpleStepper::ticking2); 
            Timer3.stop();
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }

    this->pause();
}

void SimpleStepper::setPulse(long pulse){
    switch (this->stepperTimer)
    {
        case 1:
            Timer1.setPeriod(pulse);
            break;
        case 3:
            Timer3.setPeriod(pulse);
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
}

bool SimpleStepper::step(long steps, uint8_t direction){
    //if(this->isStepping()){
    //    return false;
    //}

    this->ticksRemaining = steps * 2; //converting steps to ticks
    
    if(direction == HIGH){
      this->dirPin.setHigh();
    } else {
       this->dirPin.setLow();
    }

    return true;
}

bool SimpleStepper::step(long steps, uint8_t direction, long pulse){
    //if(this->isStepping()){
    //    return false;
    //}

    this->resume();
    this->setPulse(pulse);
 
    return  this->step(steps, direction);
}

long SimpleStepper::getRemainingSteps(){
    return ticksRemaining/2;
}

//returns the remaining steps
long SimpleStepper::stop(){
    //each step = 2 ticks
    long stepsRemaining = this->getRemainingSteps();
        switch (this->stepperTimer)
    {
        case 1:
            Timer1.stop();
            break;
        case 3:
            Timer3.stop();
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
    

    if(ticksRemaining & 1){
        ticksRemaining = 1;
    } else{
        ticksRemaining = 0;
    }

     switch (this->stepperTimer)
    {
        case 1:
            Timer1.start();
            break;
        case 3:
            Timer3.start();
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }

    return stepsRemaining;
}

void SimpleStepper::pause(){
  paused = true;
   switch (this->stepperTimer)
    {
        case 1:
            Timer1.stop();
            break;
        case 3:
            Timer3.stop();
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
  
}

void SimpleStepper::resume(){
  if(paused){
    switch (this->stepperTimer)
    {
        case 1:
            Timer1.start();
            break;
        case 3:
            Timer3.start();
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
    paused = false;
  }
}

bool SimpleStepper::isStepping(){
    return (ticksRemaining > 0);
}

bool SimpleStepper::isStopped(){
    return (ticksRemaining <= 0);
}

bool SimpleStepper::isPaused(){
  return paused;
}

void SimpleStepper::testISR()
{
    uint8_t test =0;
    test++;
}

void SimpleStepper::ticking1(){
    if(firstInstance->ticksRemaining > 0){
        //generate high/low signal for the stepper driver
        firstInstance->stepPin.toggleState();
        --firstInstance->ticksRemaining;
    }
}

void SimpleStepper::ticking2(){
    if(secondInstance->ticksRemaining > 0){
        //generate high/low signal for the stepper driver
        secondInstance->stepPin.toggleState();
        --secondInstance->ticksRemaining;
    }
}

void SimpleStepper::ticking3(){
    if(firstInstance->ticksRemaining > 0){
        //generate high/low signal for the stepper driver
        firstInstance->stepPin.toggleState();
        --firstInstance->ticksRemaining;
    }
}

void SimpleStepper::ticking4(){
    if(firstInstance->ticksRemaining > 0){
        //generate high/low signal for the stepper driver
        firstInstance->stepPin.toggleState();
        --firstInstance->ticksRemaining;
    }
}
