#include "CommFct.h"
#include "AccelMoteur.h"

void InitComm()
{
    Serial.begin(115200);
    while (!Serial);
    Serial.setTimeout(TIMEOUTTIME);//Used for parsefloat timeout. Value in ms. A value juste a little higher than the time interval of the data received is probably a good value.
    SPI.begin();
}

bool DataReception()
{
    if (Serial.available())
    {
        uint8_t counter = 0;
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
                    Serial.println("Coord recue :  X = ");
                    Serial.print(nextCoordinates.coordX);
                    Serial.println(" Y = ");
                    Serial.print(nextCoordinates.coordY);
                    Serial.println(" Z = ");
                    Serial.print(nextCoordinates.coordZ);
                    FonctionCoord2Steps(A,B,initCoordinates,nextCoordinates);
                    AccelCompute();
                }
            break;

            default:
            //There is an error during the reception of data, handle it!!
            Serial.println("Error during acquisition of coordinates");
            Serial.println("Please do something!");
            break;
        }
        return 1;
    }
    else return 0;
}