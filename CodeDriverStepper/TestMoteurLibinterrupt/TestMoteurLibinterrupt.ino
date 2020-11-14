
#include "GlobalStructures.h"
#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include "SimpleStepper.h"
#include "CommFct.h"
#include "CalculStepMotor.h"
/*
POUR L'INSTANT, ON PEUT COMPILER EN METTANT EN COMMENTAIRE L'INCLUDE DE :
CalculStepMotor.h"
*/

#define MOTORSTEPS 51200        // 360/1.8 = 200 full steps * 16 microsteps = number of steps per revolution 
#define CLOCKWISE 1             // Rotation of the stepper motor, reverse if it is swapped
#define ANTICW 0                // Rotation of the stepper motor, reverse if it is swapped
#define MAXSPEED 10000          //Maximal speed in step/second !!!!NEED TO DO SOME CALCULATION TO DEFINE CORRECTLY
#define MAXACCEL 100            //Maximal acceleration in step/s^2




/*
Recherche de librairie de contrôle de moteur via interrupt : https://forum.arduino.cc/index.php?topic=248359.0 (lien à check mais pas sûr qu'il soit utile)
https://www.forward.com.au/pfod/Robots/SpeedStepper/index.html
*/
const uint8_t DirPin = 2;
const uint8_t StepPin = 3;
const uint8_t CSPin = 4;


HighPowerStepperDriver sd;

SimpleStepper stepper(DirPin, StepPin);
uint8_t counter = 0;

Coordinates nextCoordinates = {0,0,0};
Coordinates actualCoordinates = {0,0,0}; 
Coordinates tempCoordinates = {0,0,0};

Steps MotorStep = {0,0,0};
double A = 30;//j'ai mis 30 oklm en attendant
double B = 10;//j'ai mis 10 oklm en attendant


void DataReception();
void AccelCompute(Coordinates*);
void TimerModif();


void setup()
{
    
    sd.setChipSelectPin(CSPin);

    // Drive the STEP and DIR pins low initially.
    pinMode(StepPin, OUTPUT);
    digitalWrite(StepPin, LOW);
    pinMode(DirPin, OUTPUT);
    digitalWrite(DirPin, LOW);

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
    sd.setCurrentMilliamps36v4(2800);

    // Set the number of microsteps that correspond to one full step.
    sd.setStepMode(HPSDStepMode::MicroStep256);//A definir en fct de Vitesse_max
    Serial.println("Début du test");
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

    stepper.init();

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
  if(stepper.isStopped()){

    //conter is even number
    //if(counter % 2 == 0){
    switch (counter)
    {
        case 0:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(10));
        break;
        case 1:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(20));
        break;
        case 2:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(30));
        break;
        case 3: 
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(40));
        break;
        case 4:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(50));
        break;
        case 5:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(60));
        break;
        case 6:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(70));
        break;
        case 7:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(80));
        break;
        case 8:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(90));
        break;
        case 9:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(100));
        break;
        case 10:
            stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(110));
        break;
    }
    ++counter;
  }

  if(counter == 10){
    //stop whatever the stepper is doing
    stepper.stop();
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



void AccelCompute(Coordinates*)
{}
void TimerModif()
{}




