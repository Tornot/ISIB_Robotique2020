
#ifndef GLOBAL_STRUCTURES
#define GLOBAL_STRUCTURES

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

extern Steps MotorStep;

#endif

