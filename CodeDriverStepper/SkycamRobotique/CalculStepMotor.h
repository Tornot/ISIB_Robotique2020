//############################################## CODE POUR CALCULER LE NOMBRE DE STEP POUR ATTEINDRE NEXT COORDINATES #######################################################################

#ifndef CALCUL_STEP_MOTOR
#define CALCUL_STEP_MOTOR

#include <math.h>
#include "Global.h"
//A FAIRE AU LABO : mesurer les distances A et B (en nombre de step)
//A et B on du etre declarees dans le fichier principal car sinon erreur de 
//definition multiple. Aucune idee du pourquoi malheureusement.

extern double A;
extern double B;
extern SimpleStepper* stepperTab[];
//Fonction qui mets à jour les structures de Coordonnées

void GetTargetDeltaSteps();
//Fonction qui traduit les coordonnées en nombre de step -> doit renvoyer 4 long (dans une struct)
void FonctionCoord2Steps(double a, double b, Coordinates InitCoord, Coordinates NextCoord);
void UpdateActualCoord(long L1, long L2, long L3);
void SetOrigin(double a, double b,Coordinates InitCoord);
#endif

