
#ifndef GLOBAL_H
#define GLOBAL_H
#include "SimpleStepper.h"

#define MOTORSTEPS 51200        // 360/1.8 = 200 full steps * 256 microsteps = number of steps per revolution 
#define CLOCKWISE 1             // Rotation of the stepper motor, reverse if it is swapped
#define ANTICW 0                // Rotation of the stepper motor, reverse if it is swapped
#define MAX_SPEED 10000          // Maximal speed in step/second !!!!NEED TO DO SOME CALCULATION TO DEFINE CORRECTLY
#define MAX_ACCEL 100            // Maximal acceleration in step/s^2
#define TIME_TO_REACH 5           //Time in ms to reach to target point
#define MAX_CURRENT 2800         //Max curent in one phase of motor
#define RATIO_STEP_PER_METER 773000

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

#endif
