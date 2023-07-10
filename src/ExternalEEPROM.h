#ifndef EXTERNAL_EEPROM_H
#define EXTERNALEEPROM_H

#include <Arduino.h>

class ExternalEEPROM {
    private:
        int i2c_address;
    public:
        ExternalEEPROM(int i2c_address);
        void write8bit(int address, byte value);
        void writeInt(int address, int value);
        byte read8bit(int address);
        int readInt(int address);
};

#endif