
#ifndef GLOBAL_H
#define GLOBAL_H
#include "SimpleStepper.h"

/*******************************************************************
*******************************************************************
Une partie des variables globales sont aussi définies dans SkycamRobotique.ino. Il faudrait les déplacer ici en s'assurant que le code continue de compiler et de fonctionner correctement.
*******************************************************************
*******************************************************************/
#define TEST_WITHOUT_MOTOR

#define MOTORSTEPS 1600         // 360/1.8 = 200 full steps * 256 microsteps = number of steps per revolution 
#define CLOCKWISE 1             // Rotation of the stepper motor, reverse if it is swapped
#define ANTICW 0                // Rotation of the stepper motor, reverse if it is swapped
#define MAX_SPEED 312           // Maximal speed in step/second !!!!NEED TO DO SOME CALCULATION TO DEFINE CORRECTLY
#define MAX_ACCEL 3             // Maximal acceleration in step/s^2
#define TIME_TO_REACH 10        // Time in ms to reach to target point
#define MAX_CURRENT 1400        // Max curent in one phase of motor
#define RATIO_STEP_PER_METER 24156 // Ref is 773000 steps for 1meter at 256 ustep per step

#define PERIOD_MIN 640             // Valeur arbitraire!! En us
#define PERIOD_MAX 6400
#define BREAK_THRESHOLD_DELTA_STEP 1250     // Valeur arbitraire! A CHANGER!!!!!
#define MAXIMUM_DELTA_PERIOD 160     // Valeur arbitraire! A CHANGER!!!!!
#define NBR_TICK_BETWEEN_COMPUTE 10  // Valeur arbitraire!
#define NBR_STEPPER 4

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

extern Coordinates nextCoordinates;
extern Coordinates actualCoordinates; 
extern Coordinates tempCoordinates;
extern Coordinates initCoordinates;

extern Steps TargetMotorStep;

#endif
