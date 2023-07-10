#include "ExternalEEPROM.h"

#include <Arduino.h>
#include <Wire.h>

ExternalEEPROM::ExternalEEPROM(int i2c_address){
    this->i2c_address = i2c_address;
}

void ExternalEEPROM::write8bit(int address, byte value){
    // Switch case
    Wire.beginTransmission(this->i2c_address);
    Wire.write((int)(address >> 8));
    Wire.write((int)(address & 0xFF));
    // Write data
    Wire.write(value);
    Wire.endTransmission();
    delay(5);
}


void ExternalEEPROM::writeInt(int address, int value){
    for (int i=0; i<sizeof(int); i++)
    {
        // Write 8 LSB only
        byte value_to_write = (byte) (value & 0xFF);
        this->write8bit(address, value_to_write);
        // Shift right and prepare for next loop
        value >>= 8 ;
        address++ ;
    }
}

byte ExternalEEPROM::read8bit(int address){
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

int ExternalEEPROM::readInt(int address) {
    int value = 0;
    for (int i = sizeof(int) - 1; i >= 0; i--) {
        value += (int) this->read8bit(address + i);
        value <<= 8;
    }
    value >>= 8;
    return value;
}