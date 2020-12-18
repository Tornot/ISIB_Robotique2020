//############################################## CODE POUR CALCULER LE NOMBRE DE STEP POUR ATTEINDRE NEXT COORDINATES #######################################################################
#include "CalculStepMotor.h"


void GetTargetDeltaSteps()
{/*
  stepperTab[0]->deltaStep = (long)(stepperTab[0]->actuSteps-TargetMotorStep.StepMotor1);
  stepperTab[1]->deltaStep = (long)(stepperTab[1]->actuSteps-TargetMotorStep.StepMotor2);
  stepperTab[2]->deltaStep = (long)(stepperTab[2]->actuSteps-TargetMotorStep.StepMotor3);
  stepperTab[3]->deltaStep = (long)(stepperTab[3]->actuSteps-TargetMotorStep.StepMotor4);
*/
  stepperTab[0]->deltaStep = (long)(TargetMotorStep.StepMotor1-stepperTab[0]->actuSteps);
  stepperTab[1]->deltaStep = (long)(TargetMotorStep.StepMotor2-stepperTab[1]->actuSteps);
  stepperTab[2]->deltaStep = (long)(TargetMotorStep.StepMotor3-stepperTab[2]->actuSteps);
  stepperTab[3]->deltaStep = (long)(TargetMotorStep.StepMotor4-stepperTab[3]->actuSteps);

}



//Fonction qui mets à jour les structures de Coordonnées

//Fonction qui traduit les coordonnées (en mètres) en nombre de step à parcourir pour chaque moteur. Ce nombre de pas est signé!
void FonctionCoord2Steps(double a, double b, Coordinates InitCoord, Coordinates NextCoord)
{
  double nextstepMot1 = sqrt((((a/2)-NextCoord.coordY)*((a/2)-NextCoord.coordY))+(((b/2)+NextCoord.coordX)*((b/2)+NextCoord.coordX))+((NextCoord.coordZ)*(NextCoord.coordZ)));
  double nextstepMot2 = sqrt((((a/2)-NextCoord.coordY)*((a/2)-NextCoord.coordY))+(((b/2)-NextCoord.coordX)*((b/2)-NextCoord.coordX))+((NextCoord.coordZ)*(NextCoord.coordZ)));
  double nextstepMot3 = sqrt((((a/2)+NextCoord.coordY)*((a/2)+NextCoord.coordY))+(((b/2)+NextCoord.coordX)*((b/2)+NextCoord.coordX))+((NextCoord.coordZ)*(NextCoord.coordZ)));
  double nextstepMot4 = sqrt((((a/2)+NextCoord.coordY)*((a/2)+NextCoord.coordY))+(((b/2)-NextCoord.coordX)*((b/2)-NextCoord.coordX))+((NextCoord.coordZ)*(NextCoord.coordZ)));
  
  nextstepMot1 *= RATIO_STEP_PER_METER;
  nextstepMot2 *= RATIO_STEP_PER_METER;
  nextstepMot3 *= RATIO_STEP_PER_METER;
  nextstepMot4 *= RATIO_STEP_PER_METER;

  TargetMotorStep.StepMotor1 = (long) nextstepMot1;
  TargetMotorStep.StepMotor2 = (long) nextstepMot2;
  TargetMotorStep.StepMotor3 = (long) nextstepMot3;
  TargetMotorStep.StepMotor4 = (long) nextstepMot4;

/* Original de Niels, ça fonctionne!!!
  stepperTab[0].deltaStep = (long)(InitstepMot1-nextstepMot1);
  stepperTab[1].deltaStep = (long)(InitstepMot2-nextstepMot2);
  stepperTab[2].deltaStep = (long)(InitstepMot3-nextstepMot3);
  stepperTab[3].deltaStep = (long)(InitstepMot4-nextstepMot4);*/
};

void SetOrigin(double a, double b, Coordinates InitCoord)
{
    double InitstepMot1 = sqrt((((a/2)-InitCoord.coordY)*((a/2)-InitCoord.coordY))+(((b/2)+InitCoord.coordX)*((b/2)+InitCoord.coordX))+((InitCoord.coordZ)*(InitCoord.coordZ)));
    double InitstepMot2 = sqrt((((a/2)-InitCoord.coordY)*((a/2)-InitCoord.coordY))+(((b/2)-InitCoord.coordX)*((b/2)-InitCoord.coordX))+((InitCoord.coordZ)*(InitCoord.coordZ)));
    double InitstepMot3 = sqrt((((a/2)+InitCoord.coordY)*((a/2)+InitCoord.coordY))+(((b/2)+InitCoord.coordX)*((b/2)+InitCoord.coordX))+((InitCoord.coordZ)*(InitCoord.coordZ)));
    double InitstepMot4 = sqrt((((a/2)+InitCoord.coordY)*((a/2)+InitCoord.coordY))+(((b/2)-InitCoord.coordX)*((b/2)-InitCoord.coordX))+((InitCoord.coordZ)*(InitCoord.coordZ)));
    InitstepMot1 *= RATIO_STEP_PER_METER;
    InitstepMot2 *= RATIO_STEP_PER_METER;
    InitstepMot3 *= RATIO_STEP_PER_METER;
    InitstepMot4 *= RATIO_STEP_PER_METER;
    stepperTab[0]->actuSteps = InitstepMot1;
    stepperTab[1]->actuSteps = InitstepMot2;
    stepperTab[2]->actuSteps = InitstepMot3;
    stepperTab[3]->actuSteps = InitstepMot4;
}



//Fonction qui calcule les coord grâce à L2 et L4
void UpdateActualCoord(long L1, long L2, long L3)
{

  /*actualCoordinates.coordX = ((L1*L1)-(L2*L2))/(2*B);
  actualCoordinates.coordY = ((L3*L3)-(L1*L1))/(2*A);
  actualCoordinates.coordZ = sqrt((L1*L1)-(((A/2)-actualCoordinates.coordY)*((A/2)-actualCoordinates.coordY))-(((B/2)+actualCoordinates.coordY)*((B/2)-actualCoordinates.coordY)));
*/
}
