
// This example shows basic use of a Pololu High Power Stepper Motor Driver.
//
// It shows how to initialize the driver, configure various settings, and enable
// the driver.  It shows how to send pulses to the STEP pin to step the motor
// and how to switch directions using the DIR pin.
//
// Before using this example, be sure to change the setCurrentMilliamps36v4 line
// to have an appropriate current limit for your system.  Also, see this
// library's documentation for information about how to connect the driver:
//   http://pololu.github.io/high-power-stepper-driver

#include <SPI.h>
#include <HighPowerStepperDriver.h>
#include <AccelStepper.h>
#include <Wire.h>

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

AccelStepper stepper3(AccelStepper::FULL2WIRE, StepPin, DirPin);

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
 

  stepper3.setMaxSpeed(10000.0);
  stepper3.setAcceleration(3000.0);
  stepper3.moveTo(10000); 

}


void loop()
{
  //uint8_t phase=0;
  stepper3.run();
 if (stepper3.distanceToGo() == 0)
  {
    stepper3.moveTo(-stepper3.currentPosition());
  }
}

// Sends a pulse on the STEP pin to tell the driver to take one step, and also
//delays to control the speed of the motor.
void step()
{
  // The STEP minimum high pulse width is 1.9 microseconds.
  digitalWrite(StepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(StepPin, LOW);
  delayMicroseconds(3);
}

// Writes a high or low value to the direction pin to specify what direction to
// turn the motor.
void setDirection(bool dir)
{
  // The STEP pin must not change for at least 200 nanoseconds before and after
  // changing the DIR pin.
  delayMicroseconds(1);
  digitalWrite(DirPin, dir);
  delayMicroseconds(1);
}


/*
  if (stepper3.currentPosition() > 40 && phase == 0)
  {
        stepper3.setAcceleration(50.0);
        phase =1;
  }*/
/*
  if (stepper3.currentPosition() > 1000 && phase == 0)
  {
    stepper3.setAcceleration(200.0);
    phase = 2;
  }*/
    
/*
  if (stepper3.distanceToGo() == 0)
  {
    stepper3.moveTo(-stepper3.currentPosition());
  }*/
