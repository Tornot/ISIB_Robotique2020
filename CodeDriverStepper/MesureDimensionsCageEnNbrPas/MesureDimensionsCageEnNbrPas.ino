


#include "GlobalStructures.h"
#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include "SimpleStepper.h"
#include "CommFct.h"
#include "CalculStepMotor.h"
#include "TimerOne.h"

#define MOTORSTEPS 51200        // 360/1.8 = 200 full steps * 16 microsteps = number of steps per revolution 
#define CLOCKWISE 1             // Rotation of the stepper motor, reverse if it is swapped
#define ANTICW 0                // Rotation of the stepper motor, reverse if it is swapped
#define MAXSPEED 10000          // Maximal speed in step/second !!!!NEED TO DO SOME CALCULATION TO DEFINE CORRECTLY
#define MAXACCEL 100            // Maximal acceleration in step/s^2
#define TIMETOREACH 5           //Time in ms to reach to target point
#define MAXCURRENT 2800
#define NBRSTEPSTODO 2000000    //2*10^6

/*
Recherche de librairie de contrôle de moteur via interrupt : https://forum.arduino.cc/index.php?topic=248359.0 (lien à check mais pas sûr qu'il soit utile)
https://www.forward.com.au/pfod/Robots/SpeedStepper/index.html
*/

//SPI pin: CLK = 13, MISO = 12, MOSI = 11

const uint8_t DirPin1 = 2;
const uint8_t StepPin1 = 3;
const uint8_t CSPin1 = 4;
const uint8_t stopPin = 14;

HighPowerStepperDriver sd;

SimpleStepper stepper1(DirPin1, StepPin1, 1);

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
    SPI.begin();

    InitDriver1();
    stepper1.init();

    Serial.println("Ready");
    pinMode(14, INPUT);
    while(digitalRead(stopPin) == LOW);
    delay(2000);
}


void loop()
{
    long nbrStepsDone = 0;
    long nbrRemainingSteps = 0;
    if(stepper1.isStopped())
    {
        stepper1.step(NBRSTEPSTODO, ANTICW, rpmToTickInterval(10));
    }
    if (digitalRead(stopPin) == LOW)
    {
        nbrRemainingSteps = stepper1.stop();
        Serial.print("Nbr of steps to do = ");
        Serial.println(nbrRemainingSteps);
        Serial.print("Nbr of remaining steps = ");
        Serial.println(NBRSTEPSTODO);

        nbrStepsDone = NBRSTEPSTODO - nbrRemainingSteps;
        Serial.print("Nbr of steps done = ");
        Serial.println(nbrStepsDone);
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







