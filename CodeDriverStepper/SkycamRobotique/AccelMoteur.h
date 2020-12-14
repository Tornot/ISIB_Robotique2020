#ifndef ACCEL_MOTEUR_H
#define ACCEL_MOTEUR_H

#include "CalculStepMotor.h"
#include "Global.h"
#include "SimpleStepper.h"


// Variables
extern int deltaStepMaxIndex;
extern int deltaPeriodMaxIndex;


extern Steps MotorStep;

extern SimpleStepper stepperTab[];

// Functions
void AccelCompute(uint8_t timeToReach);

#endif
