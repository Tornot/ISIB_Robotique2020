#ifndef COMM_FCT
#define COMM_FCT

#include <SPI.h>
#include "Global.h"
#include "AccelMoteur.h"
#include "CalculStepMotor.h"

#define TIMEOUTTIME 1000 //Used for parsefloat timeout. Value in ms. A value juste a little higher than the time interval of the data received is probably a good value.

//Functions declaration
void InitComm();
bool DataReception();

#endif