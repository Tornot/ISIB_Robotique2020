


#include "GlobalStructures.h"
#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include "SimpleStepper.h"
#include "CommFct.h"
#include "CalculStepMotor.h"
#include "TimerOne.h"
#include "TimerThree.h"

#define MOTORSTEPS 51200        // 360/1.8 = 200 full steps * 16 microsteps = number of steps per revolution 
#define CLOCKWISE 1             // Rotation of the stepper motor, reverse if it is swapped
#define ANTICW 0                // Rotation of the stepper motor, reverse if it is swapped
#define MAXSPEED 10000          // Maximal speed in step/second !!!!NEED TO DO SOME CALCULATION TO DEFINE CORRECTLY
#define MAXACCEL 100            // Maximal acceleration in step/s^2
#define TIMETOREACH 5           //Time in ms to reach to target point
#define MAXCURRENT 2800

/*





*/


/*
Recherche de librairie de contrôle de moteur via interrupt : https://forum.arduino.cc/index.php?topic=248359.0 (lien à check mais pas sûr qu'il soit utile)
https://www.forward.com.au/pfod/Robots/SpeedStepper/index.html
*/

//SPI pin: CLK = 13, MISO = 12, MOSI = 11

const uint8_t DirPin1 = 2;
const uint8_t StepPin1 = 3;
const uint8_t CSPin1 = 4;
const uint8_t DirPin2 = 5;
const uint8_t StepPin2 = 6;
const uint8_t CSPin2 = 7;
//!!!!!Pins for motors 3 and 4 are not defined!!!
const uint8_t DirPin3 = 2;
const uint8_t StepPin3 = 3;
const uint8_t CSPin3 = 4;
const uint8_t DirPin4 = 2;
const uint8_t StepPin4 = 3;
const uint8_t CSPin4 = 4;


HighPowerStepperDriver sd;


//extern TimerOne Timer1;
//extern TimerThree Timer3;
//extern TimerFour Timer4;
//extern TimerFive Timer5;


SimpleStepper stepper1(DirPin1, StepPin1, 1);
SimpleStepper stepper2(DirPin2, StepPin2, 3);
//SimpleStepper stepper3(DirPin3, StepPin3, 4);
//SimpleStepper stepper4(DirPin4, StepPin4, 5);
uint8_t counter = 0;

Coordinates nextCoordinates = {0,0,0};
Coordinates actualCoordinates = {0,0,0}; 
Coordinates tempCoordinates = {0,0,0};

Steps MotorStep = {0,0,0,0};
double A = 30;//j'ai mis 30 oklm en attendant
double B = 10;//j'ai mis 10 oklm en attendant

void InitDriver1();
void InitDriver2();
long rpmToTickInterval(long targetRPM);

void setup()
{
    Serial.begin(9600);
    pinMode(13, OUTPUT);//We force SPI pin mode to try to debug
    pinMode(11, OUTPUT);
    pinMode(12, INPUT);
    SPI.begin();
    InitDriver1();
    InitDriver2();
    stepper1.init();
    stepper2.init();
    FonctionCoord2Steps(A,B,actualCoordinates,nextCoordinates,MotorStep);
}

/*
void loop()
{
  //DataReception (coordonnées, formattée de manière 'X', float, 'Y', float, 'Z', float)
  DataReception();

  //Compute speed and acceleration
  //=> IN: coordinates, from a tab
  AccelCompute(&coordinates);


  //Modification of timer values => use a variable wich the timer will take at each tick
  TimerModif();

}
*/

void loop()
{
    //once the stepper finished stepping to remaining ticks/steps
    if(stepper1.isStopped()){

    switch (counter)
    {
        case 0:
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(10));
        break;
        case 1:
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(20));
        break;
        case 2:
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(30));
        break;
        case 3: 
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(35));
        break;
        case 4:
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(35));
        break;
        case 5:
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(30));
        break;
        case 6:
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(20));
        break;
        case 7:
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(10));
        break;
        case 8:
            stepper1.step(MOTORSTEPS/2, CLOCKWISE, rpmToTickInterval(5));
        break;
        case 9:
            stepper1.step(MOTORSTEPS/2, ANTICW, rpmToTickInterval(5));
        break;
        case 10:
            stepper1.step(MOTORSTEPS, ANTICW, rpmToTickInterval(10));
        break;
        case 11:
            stepper1.step(MOTORSTEPS, ANTICW, rpmToTickInterval(20));
        break;
        case 12:
            stepper1.step(MOTORSTEPS, ANTICW, rpmToTickInterval(30));
        break;
        default:
        break;
    }
    ++counter;
  }
  if(stepper2.isStopped()){

    switch (counter)
    {
        case 0:
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(10));
        break;
        case 1:
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(20));
        break;
        case 2:
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(30));
        break;
        case 3: 
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(40));
        break;
        case 4:
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(40));
        break;
        case 5:
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(30));
        break;
        case 6:
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(20));
        break;
        case 7:
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(10));
        break;
        case 8:
            stepper2.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(5));
        break;
        case 9:
            stepper2.step(MOTORSTEPS/2, CLOCKWISE, rpmToTickInterval(5));
        break;
        case 10:
            stepper2.step(MOTORSTEPS, ANTICW, rpmToTickInterval(10));
        break;
        case 11:
            stepper2.step(MOTORSTEPS, ANTICW, rpmToTickInterval(20));
        break;
        case 12:
            stepper2.step(MOTORSTEPS, ANTICW, rpmToTickInterval(30));
        break;
        default:
        break;
    }
    //++counter;    //In comment for now because otherwisewe hae 2 increment of counter
  }
  if(counter >= 14){
    //stop whatever the stepper is doing
    stepper1.stop();
    stepper2.stop();
    while(1);
  }
}

//rpm to stepper tick in micro seconds
long rpmToTickInterval(long targetRPM){
    // rotation per sec = targetRPM/60
    float stepsPerSecond = (float) targetRPM/60 * MOTORSTEPS;
    long pulseInMicroseconds = (long) (1000000L/stepsPerSecond) / 2;

    return pulseInMicroseconds;
}

void InitDriver1()
{
    Serial.println("InitDriver1");
    sd.setChipSelectPin(CSPin1);

    // Drive the STEP and DIR pins low initially.
    pinMode(StepPin1, OUTPUT);
    digitalWrite(StepPin1, LOW);
    pinMode(DirPin1, OUTPUT);
    digitalWrite(DirPin1, LOW);

    // Give the driver some time to power up.
    delay(1);
    // Reset the driver to its default settings and clear latched status
    // conditions.
    sd.resetSettings();
    sd.clearStatus();

    // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
    // for most applications, and we find that it usually works well.
    sd.setDecayMode(HPSDDecayMode::AutoMixed);
    //sd.setDecayMode(HPSDDecayMode::Mixed);
    //sd.setDecayMode(HPSDDecayMode::Slow);//Cause heavy vibrations
    // Set the current limit. You should change the number here to an appropriate
    // value for your particular system.
    sd.setCurrentMilliamps36v4(MAXCURRENT);
    // Set the number of microsteps that correspond to one full step.
    sd.setStepMode(HPSDStepMode::MicroStep256);//A definir en fct de Vitesse_max
    Serial.println("Début du test du driver 1");
    if (sd.verifySettings())
    {
        // Enable the motor outputs.
        sd.enableDriver();
        Serial.print("Status register is good = ");
        Serial.println(sd.readStatus());
    }
    else 
    {
        //Check if the settings were correctly set.
        //If we see that the verify settings are not ok, do something
        Serial.println("VerifySettings returned wrong, status register = ");
        Serial.println(sd.readStatus());
    }
}
void InitDriver2()
{
    Serial.println("InitDriver2");
    sd.setChipSelectPin(CSPin2);

    // Drive the STEP and DIR pins low initially.
    pinMode(StepPin2, OUTPUT);
    digitalWrite(StepPin2, LOW);
    pinMode(DirPin2, OUTPUT);
    digitalWrite(DirPin2, LOW);

    // Give the driver some time to power up.
    delay(1);

    // Reset the driver to its default settings and clear latched status
    // conditions.
    sd.resetSettings();
    sd.clearStatus();

    // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
    // for most applications, and we find that it usually works well.
    sd.setDecayMode(HPSDDecayMode::AutoMixed);
    //sd.setDecayMode(HPSDDecayMode::Mixed);
    //sd.setDecayMode(HPSDDecayMode::Slow);//Cause heavy vibrations
    // Set the current limit. You should change the number here to an appropriate
    // value for your particular system.
    sd.setCurrentMilliamps36v4(MAXCURRENT);

    // Set the number of microsteps that correspond to one full step.
    sd.setStepMode(HPSDStepMode::MicroStep256);//A definir en fct de Vitesse_max
    Serial.println("Début du test du driver 2");
    if (sd.verifySettings())
    {
        // Enable the motor outputs.
        sd.enableDriver();
        Serial.print("Status register is good = ");
        Serial.println(sd.readStatus());
    }
    else 
    {
        //Check if the settings were correctly set.
        //If we see that the verify settings are not ok, do something
        Serial.println("VerifySettings returned wrong, status register = ");
        Serial.println(sd.readStatus());
    }
}







