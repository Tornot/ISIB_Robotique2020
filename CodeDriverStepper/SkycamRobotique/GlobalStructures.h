
#ifndef GLOBAL_STRUCTURES
#define GLOBAL_STRUCTURES
#include "SimpleStepper.h"

typedef struct Coordinates_//coordonees en float //next est la coord que l'on veut atteindre // actual est la coord actuelle, à l'instant où on fait les calculs
{
    float coordX;
    float coordY;
    float coordZ;
} Coordinates;

typedef struct Steps_
{
    long StepMotor1;
    long StepMotor2;
    long StepMotor3;
    long StepMotor4;
} Steps;
/*
typedef struct StructTimers_
{
    TimerOne Timer1;
    TimerThree Timer3;
    //TimerFour Timer4;
    //TimerFive Timer5;
}
*/

extern Coordinates nextCoordinates;
extern Coordinates actualCoordinates; 
extern Coordinates tempCoordinates;

extern Steps MotorStep;

extern SimpleStepper stepperTab[4];
#endif
