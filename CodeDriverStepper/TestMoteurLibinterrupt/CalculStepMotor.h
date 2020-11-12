//############################################## CODE POUR CALCULER LE NOMBRE DE STEP POUR ATTEINDRE NEXT COORDINATES #######################################################################

#ifndef CALCUL_STEP_MOTOR
#define CALCUL_STEP_MOTOR

#include <math.h>
#include "GlobalStructures.h"
//A FAIRE AU LABO : mesurer les distances A et B (en nombre de step)
//A et B on du etre declarees dans le fichier principal car sinon erreur de 
//definition multiple. Aucune idee du pourquoi malheureusement.
extern double A;//j'ai mis 30 oklm en attendant
extern double B;//j'ai mis 10 oklm en attendant
//Fonction qui mets à jour les structures de Coordonnées

//Fonction qui traduit les coordonnées en nombre de step -> doit renvoyer 4 long (dans une struct)
Steps FonctionCoord2Steps(double a, double b, Coordinates InitCoord, Coordinates NextCoord, Steps stepmotor);
#endif

