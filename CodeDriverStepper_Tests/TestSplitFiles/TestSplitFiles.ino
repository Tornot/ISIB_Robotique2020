#include <SPI.h>

#include "CommFct.h"
#include "GlobalStruct.h"

struct Coordinates nextCoordinates = {0.0, 0.0, 0.0};

void setup()
{
    InitComm();
    
}

void loop()
{

    DataReception(&nextCoordinates);
    Serial.println(nextCoordinates.coordX);
    nextCoordinates.coordX = 1.2;
    Serial.println(nextCoordinates.coordX);
    
    //actualCoordinates.coordX = 1.2;

}