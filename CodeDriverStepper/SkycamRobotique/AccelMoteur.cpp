#include "AccelMoteur.h"

#define PERIODE_MIN 100//Valeur arbitraire!! En us
#define MAXIMUM_DELTA_PERIOD 10//Valeur arbitraire! A CHANGER!!!!!
#define NBR_TICK_BETWEEN_COMPUTE 6//Valeur arbitraire!


//Une variable pour la vitesse actuelle de chaque moteur stepper.actuPeriod
//Une variable pour la vitesse cible de chaque moteur stepper.tagetPeriod
//Une variable pour la prochaine vitesse de chaque moteur stepper.nextPeriod
//Une variable pour le delta période du timer de chaque moteur stepper.deltaPeriod
//Une variable pour le delta période max : deltaPeriodMax
//Une variable qui indique au moteur si il est la ref ou pas
//Une variable pour chaque moteur qui contient le nombre de pas qu'il a effectué. Cela nous fourni l'information de position


//Une variable K, un nombre de pas restant en dessous duquel on freine
//Une variable deltaStepMax qui est la plus grande distance à parcourir
//

void AccelCompute(uint8_t timeToReach)
{
    //Récupérer le deltaStep_max (devient la ref)
//Si deltaStep_max = 0 on arrête tout!


//On défini la période cible de la ref
    //Si deltaStep_max < K (avec K une constante arbitraire de nombre de pas avant de freiner)
        //Alors periodTarget = (PERIOD_MIN * K) / deltaStep_max
    //Sinon periodTarget = PERIOD_MIN
    //On assigne un periodTarget à chaque moteur


    //On trouve un delta de période pour chaque moteur. stepper.deltaPeriod = stepper.actualPeriod - stepper.targetPeriod
    //On check le max de cette période max(|deltaPeriod|) = deltaPeriodMax
    //Si deltaPeriodMax > MAXIMUM_DELTA_PERIOD
        //Alors proportionalFactor = MAXIMUM_DELTA_PERIOD/deltaPeriodMax
    //Sinon proportionalFactor = 1
    //stepper.nextPeriod = stepper.actualPeriod + proportionalFactor * stepper.deltaPeriod





    //Refaire les calculs tous les NBR_TICK_BETWEEN_COMPUTE
    //Dans l'ISR, si le moteur est la ref, il décrémente NBR_TICK_BETWEEN_COMPUTE
    //Si NBR_TICK_BETWEEN_COMPUTE == 0 alors on appelle la fonction de calcul







}
