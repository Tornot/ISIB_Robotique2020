#ifndef ACCEL_MOTEUR_H
#define ACCEL_MOTEUR_H

#include "CalculStepMotor.h"
#include "GlobalStructures.h"
#include "SimpleStepper.h"

// Variables
int deltaStepMaxIndex;
int deltaPeriodMaxIndex;

// Functions
void AccelCompute(uint8_t timeToReach);

#endif
