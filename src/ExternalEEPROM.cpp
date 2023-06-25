#include "ExternalEEPROM.h"

#include <Arduino.h>
#include <Wire.h>

ExternalEEPROM::ExternalEEPROM(int i2c_address){
    this->i2c_address = i2c_address;
}

void ExternalEEPROM::write(int address, byte value){
    // Switch case
    Wire.beginTransmission(this->i2c_address);
    Wire.write((int)(address >> 8));
    Wire.write((int)(address & 0xFF));
    // Write data
    Wire.write(value);
    Wire.endTransmission();
    delay(5);
}

byte ExternalEEPROM::read(int address){
    byte data = 0xFF;
    // Switch case
    Wire.beginTransmission(this->i2c_address);
    Wire.write((int)(address >> 8));
    Wire.write((int)(address & 0xFF));
    Wire.endTransmission();
    // Request data
    Wire.requestFrom(this->i2c_address, 1);
    // Read data
    data = Wire.read();
    return data;
}