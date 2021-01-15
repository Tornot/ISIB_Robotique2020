/**
    @file SimpleStepper.cpp
    @author Evert Chin
    @brief Fast and Simple Stepper Driver

   * This file may be redistributed under the terms of the MIT license.
   * A copy of this license has been included with this distribution in the file LICENSE.
   */

#include "SimpleStepper.h"

//Définition des variables statiques
SimpleStepper *SimpleStepper::firstInstance;
SimpleStepper *SimpleStepper::secondInstance;
SimpleStepper *SimpleStepper::thirdInstance;
SimpleStepper *SimpleStepper::fourthInstance;
volatile int SimpleStepper::tickRefresh;

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
            thirdInstance = this;
            break;
        case 5:
            fourthInstance = this;
            break;
        default:
            break;
    }
    this->dirPin = Pin(dirpin);
    this->stepPin = Pin(steppin);
    this->stepperTimer = stepperTimer;
    this->isRef = 0; 
    tickRefresh = 0;
    //this->nextPeriod = PERIOD_MAX;
    this->actuSteps = 0;
}

void SimpleStepper::init(){     //Utiliser un tableau de timer pour accéder 
    dirPin.setOutput();         //à celui que l'on veut. (du coup on évite le switch case) tabTimer[1].initalize()
    stepPin.setOutput();

    switch (this->stepperTimer)
    {
        case 1:
            Serial.print("Init of firstInstance of stepper with timer : ");
            Serial.println(this->stepperTimer);
            Timer1.initialize();
            Timer1.attachInterrupt(SimpleStepper::ticking1); 
            Timer1.stop();
            break;
        case 3:
            Serial.print("Init of secondInstance of stepper with timer : ");
            Serial.println(this->stepperTimer);
            Timer3.initialize();
            Timer3.attachInterrupt(SimpleStepper::ticking2); 
            Timer3.stop();
            break;
        case 4:
            Serial.print("Init of thirdInstance of stepper with timer : ");
            Serial.println(this->stepperTimer);
            Timer4.initialize();
            Timer4.attachInterrupt(SimpleStepper::ticking3); 
            Timer4.stop();
            break;
        case 5:
            Serial.print("Init of fourthInstance of stepper with timer : ");
            Serial.println(this->stepperTimer);
            Timer5.initialize();
            Timer5.attachInterrupt(SimpleStepper::ticking4); 
            Timer5.stop();
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
            Timer4.setPeriod(pulse);
            break;
        case 5:
            Timer5.setPeriod(pulse);
            break;
        default:
            break;
    }
}

bool SimpleStepper::step(long steps, uint8_t direction){
    //if(this->isStepping()){   //This bit of code was not commented in the 
    //    return false;         //original library, but we need to comment it
    //}                         //for our needs

    this->ticksRemaining = steps * 2; //converting steps to ticks
    if(direction == LOW)
    {
      this->dirPin.setHigh();
    }
    else
    {
       this->dirPin.setLow();
    }
    this->actuDir = direction;
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
            Timer4.stop();
            break;
        case 5:
            Timer5.stop();
            break;
        default:
            break;
    }
    
    // if odd we do one last tick to set the line at 0
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
            Timer4.start();
            break;
        case 5:
            Timer5.start();
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
            Timer4.stop();
            break;
        case 5:
            Timer5.stop();
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
                Timer4.start();
                break;
            case 5:
                Timer5.start();
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

int SimpleStepper::setTickRefresh(int setValue)
{
    tickRefresh = setValue;
}
int SimpleStepper::getTickRefresh()
{
    return tickRefresh;
}

void SimpleStepper::ticking1(){
    if(firstInstance->ticksRemaining > 0){
        //generate high/low signal for the stepper driver
        firstInstance->stepPin.toggleState();
        --firstInstance->ticksRemaining;
    }
    if ((firstInstance->actuDir == CLOCKWISE) && (firstInstance->ticksRemaining & 1))
        firstInstance->actuSteps++;
    else if ((firstInstance->actuDir == ANTICW) && (firstInstance->ticksRemaining & 1))
        firstInstance->actuSteps--;

    if (firstInstance->isRef && tickRefresh > 0)
        --tickRefresh;
}

void SimpleStepper::ticking2(){
    if(secondInstance->ticksRemaining > 0){
        //generate high/low signal for the stepper driver
        secondInstance->stepPin.toggleState();
        --secondInstance->ticksRemaining;
    }
    if ((secondInstance->actuDir == CLOCKWISE) && (secondInstance->ticksRemaining & 1))
        secondInstance->actuSteps++;
    else if ((secondInstance->actuDir == ANTICW) && (secondInstance->ticksRemaining & 1))
        secondInstance->actuSteps--;

    if (secondInstance->isRef && tickRefresh > 0)
        --tickRefresh;
}

void SimpleStepper::ticking3(){
    if(thirdInstance->ticksRemaining > 0){
        //generate high/low signal for the stepper driver
        thirdInstance->stepPin.toggleState();
        --thirdInstance->ticksRemaining;
    }
    if ((thirdInstance->actuDir == CLOCKWISE) && (thirdInstance->ticksRemaining & 1))
        thirdInstance->actuSteps++;
    else if ((thirdInstance->actuDir == ANTICW) && (thirdInstance->ticksRemaining & 1))
        thirdInstance->actuSteps--;

    if (thirdInstance->isRef && tickRefresh > 0)
        --tickRefresh;
}

void SimpleStepper::ticking4(){
    //if(fourthInstance->ticksRemaining > 0 && tickRefresh > 0) // A test!!!!
    if(fourthInstance->ticksRemaining > 0)
    {
        //generate high/low signal for the stepper driver
        fourthInstance->stepPin.toggleState();
        --fourthInstance->ticksRemaining;
    }
    if ((fourthInstance->actuDir == CLOCKWISE) && (fourthInstance->ticksRemaining & 1))
        fourthInstance->actuSteps++;
    else if ((fourthInstance->actuDir == ANTICW) && (fourthInstance->ticksRemaining & 1))
        fourthInstance->actuSteps--;

    if (fourthInstance->isRef && tickRefresh > 0)
        --tickRefresh;
}

/*TODO
-!!! On va avoir un pb quand on change de direction, car il faut absolument finir le pas en cours avant (ou pas, vu qu'on ne fait pas de toogle, 
    on serait amené à mettre la broche à 1 alors qu'elle l'est déjà, ça pourrait peut-être compenser). En gros, c'est à vérifier!!
    => il faudrait sûrement s'assurer que toutes les step pins soient à 0 au moment où on change les timers. Cela permettrait d'éviter le problème
*/
