//############################################## CODE POUR CALCULER LE NOMBRE DE STEP POUR ATTEINDRE NEXT COORDINATES #######################################################################
#include "CalculStepMotor.h"
//A FAIRE AU LABO : mesurer les distances A et B (en nombre de step)

//Fonction qui mets à jour les structures de Coordonnées

//Fonction qui traduit les coordonnées en nombre de step -> doit renvoyer 4 long (dans une struct)
void FonctionCoord2Steps(double a, double b, Coordinates InitCoord, Coordinates NextCoord){
  
  double InitstepMot1 = sqrt(square(sqrt(square((a/2)-InitCoord.coordY)+square((b/2)+InitCoord.coordX)))+square(InitCoord.coordZ));
  double nextstepMot1 = sqrt(square(sqrt(square((a/2)-NextCoord.coordY)+square((b/2)+NextCoord.coordX)))+square(NextCoord.coordZ));
  double InitstepMot2 = sqrt(square(sqrt(square((a/2)-InitCoord.coordY)+square((b/2)-InitCoord.coordX)))+square(InitCoord.coordZ));
  double nextstepMot2 = sqrt(square(sqrt(square((a/2)-NextCoord.coordY)+square((b/2)-NextCoord.coordX)))+square(NextCoord.coordZ));
  double InitstepMot3 = sqrt(square(sqrt(square((a/2)+InitCoord.coordY)+square((b/2)+InitCoord.coordX)))+square(InitCoord.coordZ));
  double nextstepMot3 = sqrt(square(sqrt(square((a/2)+NextCoord.coordY)+square((b/2)+NextCoord.coordX)))+square(NextCoord.coordZ));
  double InitstepMot4 = sqrt(square(sqrt(square((a/2)+InitCoord.coordY)+square((b/2)-InitCoord.coordX)))+square(InitCoord.coordZ));
  double nextstepMot4 = sqrt(square(sqrt(square((a/2)+NextCoord.coordY)+square((b/2)-NextCoord.coordX)))+square(NextCoord.coordZ));

    //TODO: 
  //Transformer les m de nextstepMot1/2/3/4 en pas pour mettre dans MotorStep.StepMotor1  
  //Pour cela, on a besoin de la correspondance mètre<=>pas


  MotorStep.StepMotor1 = (long)(InitstepMot1-nextstepMot1);
  MotorStep.StepMotor2 = (long)(InitstepMot2-nextstepMot2);
  MotorStep.StepMotor3 = (long)(InitstepMot3-nextstepMot3);
  MotorStep.StepMotor4 = (long)(InitstepMot4-nextstepMot4);
  
};
