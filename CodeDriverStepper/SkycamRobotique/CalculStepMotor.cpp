//############################################## CODE POUR CALCULER LE NOMBRE DE STEP POUR ATTEINDRE NEXT COORDINATES #######################################################################
#include "CalculStepMotor.h"

//Fonction qui mets à jour les structures de Coordonnées

//Fonction qui traduit les coordonnées (en mètres) en nombre de step à parcourir pour chaque moteur. Ce nombre de pas est signé!
void FonctionCoord2Steps(double a, double b, Coordinates InitCoord, Coordinates NextCoord)
{
  double InitstepMot1 = sqrt(square((a/2)-InitCoord.coordY)+square((b/2)+InitCoord.coordX)+square(InitCoord.coordZ));
  double nextstepMot1 = sqrt(square((a/2)-NextCoord.coordY)+square((b/2)+NextCoord.coordX)+square(NextCoord.coordZ));
  double InitstepMot2 = sqrt(square((a/2)-InitCoord.coordY)+square((b/2)-InitCoord.coordX)+square(InitCoord.coordZ));
  double nextstepMot2 = sqrt(square((a/2)-NextCoord.coordY)+square((b/2)-NextCoord.coordX)+square(NextCoord.coordZ));
  double InitstepMot3 = sqrt(square((a/2)+InitCoord.coordY)+square((b/2)+InitCoord.coordX)+square(InitCoord.coordZ));
  double nextstepMot3 = sqrt(square((a/2)+NextCoord.coordY)+square((b/2)+NextCoord.coordX)+square(NextCoord.coordZ));
  double InitstepMot4 = sqrt(square((a/2)+InitCoord.coordY)+square((b/2)-InitCoord.coordX)+square(InitCoord.coordZ));
  double nextstepMot4 = sqrt(square((a/2)+NextCoord.coordY)+square((b/2)-NextCoord.coordX)+square(NextCoord.coordZ));

  InitstepMot1 *= RATIO_STEP_PER_METER;
  nextstepMot1 *= RATIO_STEP_PER_METER;
  InitstepMot2 *= RATIO_STEP_PER_METER;
  nextstepMot2 *= RATIO_STEP_PER_METER;
  InitstepMot3 *= RATIO_STEP_PER_METER;
  nextstepMot3 *= RATIO_STEP_PER_METER;
  InitstepMot4 *= RATIO_STEP_PER_METER;
  nextstepMot4 *= RATIO_STEP_PER_METER;

  stepperTab[0].deltaStep = (long)(InitstepMot1-nextstepMot1);
  stepperTab[1].deltaStep = (long)(InitstepMot2-nextstepMot2);
  stepperTab[2].deltaStep = (long)(InitstepMot3-nextstepMot3);
  stepperTab[3].deltaStep = (long)(InitstepMot4-nextstepMot4);
};



//Fonction qui calcule les coord grâce à L2 et L4
void UpdateActualCoord(long L2, long L4){
   float alpha = acos((L2*L2+A*A-L4*L4)/2*L2*A);
   float x2 = L2*sin(alpha);
   float y2 = L2*cos(alpha);
   actualCoordinates.coordX = (B/2) - x2;
   actualCoordinates.coordY = (A/2) - y2;
}
