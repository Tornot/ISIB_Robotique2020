#include "AccelMoteur.h"

#define PERIOD_MIN 100             //Valeur arbitraire!! En us
#define BREAK_THRESHOLD_DELTA_STEP 10     //Valeur arbitraire! A CHANGER!!!!!
#define MAXIMUM_DELTA_PERIOD 10     //Valeur arbitraire! A CHANGER!!!!!
#define NBR_TICK_BETWEEN_COMPUTE 6  //Valeur arbitraire!
#define NBR_STEPPER 4


//Une variable pour chaque moteur qui contient le nombre de pas qu'il a effectué : stepper.actuStep Cela nous fourni l'information de position (on a implémenté actuTicks qui veut 2*actuStep)
//Une variable pour connaitre l'écart entre la consigne en step et le nombre de step actuel stepper.deltaStep
//Une variable pour la vitesse actuelle de chaque moteur stepper.actuPeriod
//Une variable pour la vitesse cible de chaque moteur stepper.tagetPeriod
//Une variable pour la prochaine vitesse de chaque moteur stepper.nextPeriod
//Une variable pour le delta période du timer de chaque moteur stepper.deltaPeriod
//Une variable pour le delta période max : deltaPeriodMax
//Une variable qui indique au moteur si il est la ref ou pas


//Une variable K, un nombre de pas restant en dessous duquel on freine
//Une variable deltaStepMax qui est la plus grande distance à parcourir
//



void AccelCompute(uint8_t timeToReach)
{
    //TODO: Mettre à jour les coord actuelles en mètres avant d'appeler FonctionCoord2Steps()
    /////////////////////
    /////////On update que les coord en X et en Y!!! On va avoir des erreurs!!!!!!!!!
    UpdateActualCoord(stepperTab[0].actuSteps,stepperTab[1].actuSteps,stepperTab[2].actuSteps);
    Serial.println("On a un while(1) après, il faut le virer quand on a corrigé. Se trouve dans AccelMoteur.cpp");
    while(1);//Tant qu'on n'a pas corrigé l'erreur d'avant, on ne fait rien!!
    //Calculer le deltaStep pour chaque moteur
    FonctionCoord2Steps(A,B,actualCoordinates,nextCoordinates);


    //Récupérer le deltaStep_max (devient la ref). C'est le moteur qui doit faire le plus de steps
    deltaStepMaxIndex = 0;
    for(int i = 0; i < NBR_STEPPER; i++ ){
        if( abs(stepperTab[deltaStepMaxIndex].deltaStep) <= abs(stepperTab[i].deltaStep) ){
            deltaStepMaxIndex = i;
        }
    }
    //Si deltaStep_max = 0 on arrête tout!
    if(stepperTab[deltaStepMaxIndex].deltaStep == 0){
        for (int i = 0; i < NBR_STEPPER; i++)
        {
            stepperTab[i].stop();
        }
    }

    //On définit la période cible de la ref
    //Si deltaStepMax < K (avec K une constante arbitraire de nombre de pas avant de freiner (BREAK_THRESHOLD_DELTA_STEP))
        //Alors periodTarget = (PERIOD_MIN * K) / deltaStep_max
    //Sinon periodTarget = PERIOD_MIN
    //On assigne un periodTarget à chaque moteur
    float targetPeriodRatio = 1.0;
    if(abs(stepperTab[deltaStepMaxIndex].deltaStep) < BREAK_THRESHOLD_DELTA_STEP){
        targetPeriodRatio = (float)BREAK_THRESHOLD_DELTA_STEP / (float)abs(stepperTab[deltaStepMaxIndex].deltaStep);
        // facteur de augmentation de la targetPeriod du stepper qui va le plus vite pcq il ne peut pas aller plus vite que PERIOD_MIN
        // tous les autres steppers devront être diminués de ce facteur proportionnellement
    }

    //On trouve un delta de période pour chaque moteur. stepper.deltaPeriod = stepper.actualPeriod - stepper.targetPeriod
    for (int i = 0; i < NBR_STEPPER; i++)
    {
        stepperTab[i].targetPeriod = PERIOD_MIN * targetPeriodRatio;
        stepperTab[i].deltaPeriod = stepperTab[i].targetPeriod - stepperTab[i].actuPeriod;
    }

    //On check le max de cette période max(|deltaPeriod|) = deltaPeriodMax
    deltaPeriodMaxIndex = 0;
    for(int i = 0; i < NBR_STEPPER; i++ ){
        if( abs(stepperTab[deltaPeriodMaxIndex].deltaPeriod) <= abs(stepperTab[i].deltaPeriod) ){
            stepperTab[deltaPeriodMaxIndex].isRef = 0;
            deltaPeriodMaxIndex = i;
            stepperTab[deltaPeriodMaxIndex].isRef = 1;
        }
    }

    //Si deltaPeriodMax > MAXIMUM_DELTA_PERIOD
        //Alors proportionalFactor = MAXIMUM_DELTA_PERIOD/deltaPeriodMax
    //Sinon proportionalFactor = 1
    //stepper.nextPeriod = stepper.actualPeriod + proportionalFactor * stepper.deltaPeriod
    float satDeltaPeriodRatio = 1.0;
    if(abs(stepperTab[deltaPeriodMaxIndex].deltaPeriod) > MAXIMUM_DELTA_PERIOD){ //si on fait un saut de période trop grand (grande différence de vitesse)
        satDeltaPeriodRatio = (float)MAXIMUM_DELTA_PERIOD / (float)abs(stepperTab[deltaPeriodMaxIndex].deltaPeriod);
    }

    for (int i = 0; i < NBR_STEPPER; i++)
    {
        stepperTab[i].actuPeriod += (long)((float)stepperTab[i].deltaPeriod * satDeltaPeriodRatio);
    }

    //Remplir les timers comme on le souhaite.
    for (int i = 0; i < NBR_STEPPER; i++)
    {
        if(stepperTab[i].deltaStep >= 0)
            stepperTab[i].step(stepperTab[i].deltaStep, CLOCKWISE, stepperTab[i].actuPeriod);
        else
            stepperTab[i].step(stepperTab[i].deltaStep, ANTICW, stepperTab[i].actuPeriod);
    }
}

