

#ifndef COMM_FCT
#define COMM_FCT

#include <SPI.h>
#include "GlobalStruct.h"

#define TIMEOUTTIME 50

//Variables Declaration



//Functions declaration
void InitComm();
void DataReception(struct Coordinates *nextCoordinates);


#endif