#ifndef ANODELEDRGB_h
#define ANODELEDRGB_h

#include <Arduino.h>
#include "ColorLEDRGB.h"

class AnodeLEDRGB {
    private:
        int redPIN;
        int greenPIN;
        int bluePIN;
    public:
        AnodeLEDRGB(int redPIN, int greenPIN, int bluePIN);
        void turnON(ColorLEDRGB color);
        void turnOFF();
};

#endif