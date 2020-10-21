
#include <Wire.h>
#include "CommFct.h"


void DataReception()
{

    if (Serial.available())
    {
        char cData;
        float fCoord
        data = Serial.read()
        switch data
        {
            case 'x':
            if (Serial.available())
            {
                fCoord = Serial.parseFloat(SKIP_NONE);
                cordinates.coordX = fCoord;
            }
            break;

            case 'y':
            break;

            case 'z':
            break;

            default:
            break;

        }



    }

}