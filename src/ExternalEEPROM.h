#ifndef EXTERNAL_EEPROM_H
#define EXTERNALEEPROM_H

#include <Arduino.h>

class ExternalEEPROM {
    private:
        int i2c_address;
    public:
        ExternalEEPROM(int i2c_address);
        void write(int address, byte value);
        byte read(int address);
};

#endif