
#include "CommFct.h"


void InitComm()
{
    Serial.begin(9600);
    while (!Serial);
    Serial.setTimeout(TIMEOUTTIME);//Used for parsefloat timeout. A value juste a little higher than the time interval of the data received is probably a good value.

    SPI.begin(); 
}

void DataReception(struct Coordinates *nextCoordinates)
{
    nextCoordinates->coordX = 1.2;
    //actualCoordinates.coordX = 1.2;
}