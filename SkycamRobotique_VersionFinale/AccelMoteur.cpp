#include "AccelMoteur.h"

//AccelCompute s'occupe de calculer les timers associés à chaque moteur afin de régler leur vitesse.
//Cette fonction ne retourne rien, tout est fait une fois que son appel est terminé.
//Elle doit être appelée tout les NBR_TICK_BETWEEN_COMPUTE afin d'être efficace.
void AccelCompute()
{
//Calcule le nombre de pas à réaliser pour chaque moteur (met à jour stepperTab[x]->deltaStep)
    GetTargetDeltaSteps();

//Défini la ref et le maximum de pas à faire
    //Récupérer le deltaStep_max (devient la ref). C'est le moteur qui doit faire le plus de steps
    deltaStepMaxIndex = 0;
    for(int i = 0; i < NBR_STEPPER; i++ )
    {
        if( abs(stepperTab[deltaStepMaxIndex]->deltaStep) <= abs(stepperTab[i]->deltaStep) )
        {
            stepperTab[deltaStepMaxIndex]->isRef = 0;
            deltaStepMaxIndex = i;
            stepperTab[deltaStepMaxIndex]->isRef = 1;
        }
    }

//Si il n'y a plus de pas à faire, on arrête tout! (deltaStep_max = 0)
    if(stepperTab[deltaStepMaxIndex]->deltaStep < (NBR_TICK_BETWEEN_COMPUTE/2))
    {
        for (int i = 0; i < NBR_STEPPER; i++)
        {
            stepperTab[i]->stop();
        }
    }

//On freine si il reste peu de pas à faire.
    float targetPeriodBrakeRatio = 1.0;
    if(abs(stepperTab[deltaStepMaxIndex]->deltaStep) < BREAK_THRESHOLD_DELTA_STEP)
    {
        targetPeriodBrakeRatio = (float)BREAK_THRESHOLD_DELTA_STEP / (float)abs(stepperTab[deltaStepMaxIndex]->deltaStep);
        // facteur d'augmentation de la targetPeriod du stepper qui va le plus vite pcq il ne peut pas aller plus vite que PERIOD_MIN
        // tous les autres steppers devront être diminués de ce facteur proportionnellement
    }

//On trouve le rapport de vitesse target de chaque moteur par rapport à la ref (ratio > 1 car période)
    float targetPeriodMinRatio[4] = {1.0, 1.0, 1.0, 1.0};
    for(int i = 0; i < NBR_STEPPER; i++)
    {
        targetPeriodMinRatio[i] = abs((float)stepperTab[deltaStepMaxIndex]->deltaStep / (float)stepperTab[i]->deltaStep);
    }

//On trouve un delta de période pour chaque moteur.
    for (int i = 0; i < NBR_STEPPER; i++)
    {
        stepperTab[i]->targetPeriod = (float)PERIOD_MIN * targetPeriodBrakeRatio * targetPeriodMinRatio[i];
        stepperTab[i]->deltaPeriod = stepperTab[i]->targetPeriod - stepperTab[i]->actuPeriod;
    }

//On check qui a le plus grand deltaPeriod à faire
    deltaPeriodMaxIndex = 0;
    for(int i = 0; i < NBR_STEPPER; i++ )
    {
        if( abs(stepperTab[deltaPeriodMaxIndex]->deltaPeriod) <= abs(stepperTab[i]->deltaPeriod) )
        {
            //Serial.print("Test : ");

            //stepperTab[deltaPeriodMaxIndex].isRef = 0;
            deltaPeriodMaxIndex = i;
            //stepperTab[deltaPeriodMaxIndex].isRef = 1;
        }
    }

//On réduit les variations de vitesse par rapport à celui qui a la plus grande variation et on modifie les périodes de chaque stepper.
//Cela permet d'avoir des accélération différentes pour chaque moteur et qu'ils atteignent leur vitesse de croisière en même temps.
    float satDeltaPeriodRatio = 1.0;
    if(abs(stepperTab[deltaPeriodMaxIndex]->deltaPeriod) > MAXIMUM_DELTA_PERIOD)
    { //si on fait un saut de période trop grand (grande différence de vitesse)
        satDeltaPeriodRatio = (float)MAXIMUM_DELTA_PERIOD / (float)abs(stepperTab[deltaPeriodMaxIndex]->deltaPeriod);
    }
    for (int i = 0; i < NBR_STEPPER; i++)
    {
        stepperTab[i]->actuPeriod += (long)((float)stepperTab[i]->deltaPeriod * satDeltaPeriodRatio);
    }

//On charge les valeurs dans les timers et on reset le nombre de ticks à réaliser avant de recalculer les vitesses.
    for (int i = 0; i < NBR_STEPPER; i++)
    {
        if(stepperTab[i]->deltaStep >= 0)
            stepperTab[i]->step(abs(stepperTab[i]->deltaStep), CLOCKWISE, stepperTab[i]->actuPeriod);
        else
            stepperTab[i]->step(abs(stepperTab[i]->deltaStep), ANTICW, stepperTab[i]->actuPeriod);
    }
    SimpleStepper::setTickRefresh(NBR_TICK_BETWEEN_COMPUTE);
}

//Ce que l'on veut, c'est que chaque moteur aille à une fraction de la vitesse du moteur le plus rapide. Il faut donc calculer le nombre
//de pas de chaque moteur, définir la vitesse target de celui qui doit en faire le plus (la ref) et réduire la vitesse target des autres de manière proportionnelle
//au nombre de pas qu'ils doivent faire par rapport à la ref.