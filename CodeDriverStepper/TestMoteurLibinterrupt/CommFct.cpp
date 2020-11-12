
#include "CommFct.h"

void InitComm()
{
    Serial.begin(9600);
    while (!Serial);
    Serial.setTimeout(TIMEOUTTIME);//Used for parsefloat timeout. A value juste a little higher than the time interval of the data received is probably a good value.

    SPI.begin();
}

void DataReception()
{
    if (Serial.available())
    {
        char cData;
        float fCoord;
        cData = Serial.read();
        switch (cData)    //Get coordinates and change them together
        {
            case 'x':
                if (Serial.available())
                {
                    fCoord = Serial.parseFloat(SKIP_NONE);//Get the floating point number for X 
                    tempCoordinates.coordX = fCoord;
                }
            break;

            case 'y':
                if (Serial.available())
                {
                    fCoord = Serial.parseFloat(SKIP_NONE);//Get the floating point number for Y
                    tempCoordinates.coordY = fCoord;
                }
            break;

            case 'z':
                if (Serial.available())
                {
                    fCoord = Serial.parseFloat(SKIP_NONE);//Get the floating point number for Z
                    nextCoordinates.coordX = tempCoordinates.coordX;
                    nextCoordinates.coordY = tempCoordinates.coordY;
                    nextCoordinates.coordZ = fCoord;
                }
            break;

            default:
            //There is an error during the reception of data, handle it!!
            Serial.println("Error during acquisition of coordinates");
            Serial.println("Please do something!");
            break;
        }
    }
}