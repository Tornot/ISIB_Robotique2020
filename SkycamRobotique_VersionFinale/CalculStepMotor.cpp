//############################################## CODE POUR CALCULER LE NOMBRE DE STEP POUR ATTEINDRE NEXT COORDINATES #######################################################################
#include "CalculStepMotor.h"

//Update the number of steps remaining
void GetTargetDeltaSteps()
{
  stepperTab[0]->deltaStep = (long)(TargetMotorStep.StepMotor1-stepperTab[0]->actuSteps);
  stepperTab[1]->deltaStep = (long)(TargetMotorStep.StepMotor2-stepperTab[1]->actuSteps);
  stepperTab[2]->deltaStep = (long)(TargetMotorStep.StepMotor3-stepperTab[2]->actuSteps);
  stepperTab[3]->deltaStep = (long)(TargetMotorStep.StepMotor4-stepperTab[3]->actuSteps);
}

//Fonction qui traduit les coordonnées fournies (en mètres) en un nombre de steps absolu à rejoindre. Ce nombre de pas est signé!
void FonctionCoord2Steps(double a, double b, Coordinates InitCoord, Coordinates NextCoord)
{
  double nextstepMot1 = sqrt((((a/2)-NextCoord.coordY)*((a/2)-NextCoord.coordY))+(((b/2)+NextCoord.coordX)*((b/2)+NextCoord.coordX))+((NextCoord.coordZ)*(NextCoord.coordZ)));
  double nextstepMot2 = sqrt((((a/2)-NextCoord.coordY)*((a/2)-NextCoord.coordY))+(((b/2)-NextCoord.coordX)*((b/2)-NextCoord.coordX))+((NextCoord.coordZ)*(NextCoord.coordZ)));
  double nextstepMot3 = sqrt((((a/2)+NextCoord.coordY)*((a/2)+NextCoord.coordY))+(((b/2)+NextCoord.coordX)*((b/2)+NextCoord.coordX))+((NextCoord.coordZ)*(NextCoord.coordZ)));
  double nextstepMot4 = sqrt((((a/2)+NextCoord.coordY)*((a/2)+NextCoord.coordY))+(((b/2)-NextCoord.coordX)*((b/2)-NextCoord.coordX))+((NextCoord.coordZ)*(NextCoord.coordZ)));

  TargetMotorStep.StepMotor1 = (long) (nextstepMot1 * RATIO_STEP_PER_METER);
  TargetMotorStep.StepMotor2 = (long) (nextstepMot2 * RATIO_STEP_PER_METER);
  TargetMotorStep.StepMotor3 = (long) (nextstepMot3 * RATIO_STEP_PER_METER);
  TargetMotorStep.StepMotor4 = (long) (nextstepMot4 * RATIO_STEP_PER_METER);
};

//Fixe le nombre de steps de départ de tous les moteurs en prenant en compte les dimensions du repère et la position de départ de la nacelle.
void SetOrigin(double a, double b, Coordinates InitCoord)
{
    double InitstepMot1 = sqrt((((a/2)-InitCoord.coordY)*((a/2)-InitCoord.coordY))+(((b/2)+InitCoord.coordX)*((b/2)+InitCoord.coordX))+((InitCoord.coordZ)*(InitCoord.coordZ)));
    double InitstepMot2 = sqrt((((a/2)-InitCoord.coordY)*((a/2)-InitCoord.coordY))+(((b/2)-InitCoord.coordX)*((b/2)-InitCoord.coordX))+((InitCoord.coordZ)*(InitCoord.coordZ)));
    double InitstepMot3 = sqrt((((a/2)+InitCoord.coordY)*((a/2)+InitCoord.coordY))+(((b/2)+InitCoord.coordX)*((b/2)+InitCoord.coordX))+((InitCoord.coordZ)*(InitCoord.coordZ)));
    double InitstepMot4 = sqrt((((a/2)+InitCoord.coordY)*((a/2)+InitCoord.coordY))+(((b/2)-InitCoord.coordX)*((b/2)-InitCoord.coordX))+((InitCoord.coordZ)*(InitCoord.coordZ)));
    
    stepperTab[0]->actuSteps = InitstepMot1 * RATIO_STEP_PER_METER;
    stepperTab[1]->actuSteps = InitstepMot2 * RATIO_STEP_PER_METER;
    stepperTab[2]->actuSteps = InitstepMot3 * RATIO_STEP_PER_METER;
    stepperTab[3]->actuSteps = InitstepMot4 * RATIO_STEP_PER_METER;
}
