#include <Arduino.h>
#include "AnodeLEDRGB.h"

AnodeLEDRGB::AnodeLEDRGB(int redPIN, int greenPIN, int bluePIN){
    this->redPIN = redPIN;
    this->greenPIN = greenPIN;
    this->bluePIN = bluePIN;
};


void AnodeLEDRGB::turnON(ColorLEDRGB color){
    switch (color)
    {
    case ColorLEDRGB::RED:
        digitalWrite(redPIN, LOW);
        digitalWrite(greenPIN, HIGH);
        digitalWrite(bluePIN, HIGH);
        break;
    case ColorLEDRGB::GREEN:
        digitalWrite(redPIN, HIGH);
        digitalWrite(greenPIN, LOW);
        digitalWrite(bluePIN, HIGH);
        break;
    case ColorLEDRGB::BLUE:
        digitalWrite(redPIN, HIGH);
        digitalWrite(greenPIN, HIGH);
        digitalWrite(bluePIN, LOW);
        break;
    case ColorLEDRGB::YELLOW:
        digitalWrite(redPIN, LOW);
        digitalWrite(greenPIN, LOW);
        digitalWrite(bluePIN, HIGH);
        break;
    case ColorLEDRGB::PURPLE:
        digitalWrite(redPIN, LOW);
        digitalWrite(greenPIN, HIGH);
        digitalWrite(bluePIN, LOW);
        break;
    case ColorLEDRGB::CYAN:
        digitalWrite(redPIN, HIGH);
        digitalWrite(greenPIN, LOW);
        digitalWrite(bluePIN, LOW);
        break;
    case ColorLEDRGB::WHITE:
        digitalWrite(redPIN, LOW);
        digitalWrite(greenPIN, LOW);
        digitalWrite(bluePIN, LOW);
        break;
    default:
        digitalWrite(redPIN, HIGH);
        digitalWrite(greenPIN, HIGH);
        digitalWrite(bluePIN, HIGH);
        break;
    }
};

void AnodeLEDRGB::turnOFF(){
    digitalWrite(redPIN, HIGH);
    digitalWrite(greenPIN, HIGH);
    digitalWrite(bluePIN, HIGH);
};