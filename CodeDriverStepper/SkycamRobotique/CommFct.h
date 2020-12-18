

#ifndef COMM_FCT
#define COMM_FCT

#include <SPI.h>
#include "Global.h"
#include "AccelMoteur.h"
#include "CalculStepMotor.h"

#define TIMEOUTTIME 50

//Functions declaration
void InitComm();
bool DataReception();


#endif