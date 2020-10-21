
#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <SimpleStepper.h>

#define MOTORSTEPS 1600        // 360/1.8 = 200 full steps * 16 microsteps = number of steps per revolution 
#define CLOCKWISE 1            // Rotation of the stepper motor, reverse if it is swapped
#define ANTICW 0               // Rotation of the stepper motor, reverse if it is swapped


/*
Recherche de librairie de contrôle de moteur via interrupt : https://forum.arduino.cc/index.php?topic=248359.0 (lien à check mais pas sûr qu'il soit utile)
https://www.forward.com.au/pfod/Robots/SpeedStepper/index.html
*/
const uint8_t DirPin = 2;
const uint8_t StepPin = 3;
const uint8_t CSPin = 4;

// This period is the length of the delay between steps, which controls the
// stepper motor's speed.  You can increase the delay to make the stepper motor
// go slower.  If you decrease the delay, the stepper motor will go faster, but
// there is a limit to how fast it can go before it starts missing steps.
const uint16_t StepPeriodUs = 2000;

HighPowerStepperDriver sd;

SimpleStepper stepper(DirPin, StepPin);
uint8_t counter = 0;

struct Coordinates//coordonees en float 
{
    float coordX;
    float coordY;
    float coordZ;
}coordinates;






void DataReception();
void AccelCompute(struct Coordinates*);
void TimerModif();


void setup()
{
  SPI.begin();
  Serial.begin(9600);
  while (!Serial);
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
  //sd.setDecayMode(HPSDDecayMode::AutoMixed);
  //sd.setDecayMode(HPSDDecayMode::Mixed);
  sd.setDecayMode(HPSDDecayMode::Slow);
  // Set the current limit. You should change the number here to an appropriate
  // value for your particular system.
  sd.setCurrentMilliamps36v4(2800);

  // Set the number of microsteps that correspond to one full step.
  sd.setStepMode(HPSDStepMode::MicroStep8);//A definir en fct de Vitesse_max
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

}

void loop()
{
  //DataReception (coord)
  DataReception();

  //Compute speed and acceleration
  //=> IN: coordinates, from a tab
  AccelCompute(&coordinates);


  //Modification of timer values => use a variable wich the timer will take at each tick
  TimerModif();

}

/*
void loop()
{
  

  //once the stepper finished stepping to remaining ticks/steps
  if(stepper.isStopped()){

    //conter is even number
    if(counter % 2 == 0){
      //do a full rotation clockwise at 20rpm
      stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(20));
    } else {
      //do a full rotation clockwise at 10rpm
      stepper.step(MOTORSTEPS, ANTICW, rpmToTickInterval(10));
    }

    ++counter;
  }

  if(counter == 10){
    //stop whatever the stepper is doing
    stepper.stop();
  }
}

//rpm to stepper tick in micro seconds
long rpmToTickInterval(long targetRPM){
    // rotation per sec = targetRPM/60
    float stepsPerSecond = (float) targetRPM/60 * MOTORSTEPS;
    long pulseInMicroseconds = (long) (1000000L/stepsPerSecond) / 2;

    return pulseInMicroseconds;
}
*/

void DataReception()
{}
void AccelCompute(struct Coordinates*)
{}
void TimerModif()
{}
