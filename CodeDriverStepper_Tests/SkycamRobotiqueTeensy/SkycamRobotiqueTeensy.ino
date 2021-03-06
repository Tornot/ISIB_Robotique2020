


#include "GlobalStructures.h"
#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include "SimpleStepper.h"
#include "CommFct.h"
#include "CalculStepMotor.h"
#include "TimerOne.h"
#include "TimerThree.h"
#include "TimerFour.h"
#include "TimerFive.h"

#define MOTORSTEPS 51200        // 360/1.8 = 200 full steps * 256 microsteps = number of steps per revolution 
#define CLOCKWISE 1             // Rotation of the stepper motor, reverse if it is swapped
#define ANTICW 0                // Rotation of the stepper motor, reverse if it is swapped
#define MAXSPEED 10000          // Maximal speed in step/second !!!!NEED TO DO SOME CALCULATION TO DEFINE CORRECTLY
#define MAXACCEL 100            // Maximal acceleration in step/s^2
#define TIMETOREACH 5           //Time in ms to reach to target point
#define MAXCURRENT 2800         //Max curent in one phase of motor



/*
Recherche de librairie de contrôle de moteur via interrupt : https://forum.arduino.cc/index.php?topic=248359.0 (lien à check mais pas sûr qu'il soit utile)
https://www.forward.com.au/pfod/Robots/SpeedStepper/index.html
*/

//SPI pin: CLK = 52, MISO = 50, MOSI = 51

const uint8_t DirPin1 = 2;
const uint8_t StepPin1 = 3;
const uint8_t CSPin1 = 4;
const uint8_t DirPin2 = 5;
const uint8_t StepPin2 = 6;
const uint8_t CSPin2 = 7;
//!!!!!Pins for motors 3 and 4 are not defined!!!
const uint8_t DirPin3 = 22;
const uint8_t StepPin3 = 24;
const uint8_t CSPin3 = 26;
const uint8_t DirPin4 = 23;
const uint8_t StepPin4 = 25;
const uint8_t CSPin4 = 27;


HighPowerStepperDriver sd;

SimpleStepper stepper1(DirPin1, StepPin1, 1);
SimpleStepper stepper2(DirPin2, StepPin2, 3);
SimpleStepper stepper3(DirPin3, StepPin3, 4);
SimpleStepper stepper4(DirPin4, StepPin4, 5);
uint8_t counter = 0;

Coordinates nextCoordinates = {0,0,0};
Coordinates actualCoordinates = {0,0,0}; 
Coordinates tempCoordinates = {0,0,0};

Steps MotorStep = {0,0,0,0};
double A = 300;//j'ai mis 30 oklm en attendant
double B = 100;//j'ai mis 10 oklm en attendant

void InitDriver1();
void InitDriver2();
void InitDriver3();
void InitDriver4();

void TestTourner2Moteurs();
long ValAbs(long x);
long rpmToTickInterval(long targetRPM);

void setup()
{
    //Serial.begin(9600);   //Doublon aec InitComm()
    InitComm();
    SPI.begin();
    InitDriver1();
    InitDriver2();
    InitDriver3();
    InitDriver4();

    stepper1.init();
    stepper2.init();
    stepper3.init();
    stepper4.init();
    FonctionCoord2Steps(A,B,actualCoordinates,nextCoordinates);

    Serial.println("Ready");
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
{ //Ici on a du code qui devrait pouvoir faire tourner les 4 moteurs à une vitesse fixe jusqu'à la position voulue

    float v1=0;
    float v2=0;
    float v3=0;
    float v4=0;
    long delaiTimer1 = 0;
    long delaiTimer2 = 0;
    long delaiTimer3 = 0;
    long delaiTimer4 = 0;


/*
    if (DataReception()) 
    {

        FonctionCoord2Steps(A,B,actualCoordinates,nextCoordinates);

        //v1 = nbr pas à faire / deltaTemps (5ms)
        //v1 = MotorStep.StepMotor1 / 0.005;
        //Convertir la vitesse en délai pour timer
        //delaiTimer1 =  (0.005/MotorStep.StepMotor1)/2; // On divise par 2 pcq on a 2 ticks par pas 
        //stepper1.step(MotorStep.StepMotor1, CLOCKWISE, delaiTimer1);


        if (MotorStep.StepMotor1 > 0)
            stepper1.step(MotorStep.StepMotor1, CLOCKWISE, rpmToTickInterval(10));
        else 
            stepper1.step(-MotorStep.StepMotor1, ANTICW, rpmToTickInterval(10));
        if (MotorStep.StepMotor2 > 0) 
            stepper2.step(MotorStep.StepMotor2, CLOCKWISE, rpmToTickInterval(10));
        else 
            stepper2.step(-MotorStep.StepMotor2, ANTICW, rpmToTickInterval(10));
        if (MotorStep.StepMotor3 > 0) 
            stepper3.step(MotorStep.StepMotor3, CLOCKWISE, rpmToTickInterval(10));
        else 
            stepper3.step(-MotorStep.StepMotor3, ANTICW, rpmToTickInterval(10));
        if (MotorStep.StepMotor4 > 0) 
            stepper4.step(MotorStep.StepMotor4, CLOCKWISE, rpmToTickInterval(10));
        else 
            stepper4.step(-MotorStep.StepMotor4, ANTICW, rpmToTickInterval(10));

        actualCoordinates = nextCoordinates; //On part du principe que lors de la prochaine réception, on a atteint le point voulu. 
        //C'est pas très clean mais on fera aec pour l'instant.
    }*/


    TestTourner2Moteurs();
}

//rpm to stepper tick in micro seconds
long rpmToTickInterval(long targetRPM){
    // rotation per sec = targetRPM/60
    float stepsPerSecond = (float) targetRPM/60 * MOTORSTEPS;
    long pulseInMicroseconds = (long) (1000000L/stepsPerSecond) / 2;

    return pulseInMicroseconds;
}

long ValAbs(long x)
{
    if (x>=0) return x;
    else return -x;
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

void InitDriver3()
{
    Serial.println("InitDriver3");
    sd.setChipSelectPin(CSPin3);

    // Drive the STEP and DIR pins low initially.
    pinMode(StepPin3, OUTPUT);
    digitalWrite(StepPin3, LOW);
    pinMode(DirPin3, OUTPUT);
    digitalWrite(DirPin3, LOW);

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
    Serial.println("Début du test du driver 3");
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

void InitDriver4()
{
    Serial.println("InitDriver4");
    sd.setChipSelectPin(CSPin4);

    // Drive the STEP and DIR pins low initially.
    pinMode(StepPin4, OUTPUT);
    digitalWrite(StepPin4, LOW);
    pinMode(DirPin4, OUTPUT);
    digitalWrite(DirPin4, LOW);

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
    Serial.println("Début du test du driver 4");
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





void TestTourner2Moteurs()
{
        //once the stepper finished stepping to remaining ticks/steps
    if(stepper1.isStopped()){

    switch (counter)
    {
        case 0:
            stepper1.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(10));
            stepper3.step(MOTORSTEPS*5, CLOCKWISE, rpmToTickInterval(10));
            stepper4.step(MOTORSTEPS*5, CLOCKWISE, rpmToTickInterval(10));
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
    stepper3.stop();
    stepper4.stop();
    while(1);
  }
}




