#ifndef EEPROM_MEMORY_MANAGER_H
#define EEPROM_MEMORY_MANAGER_H

#include <Arduino.h>

#include "DayAlarm.h"
#include "ExternalEEPROM.h"

class EEPROMMemoryManager {
    private:
        byte state;
        DayAlarm *alarms;
        int numberOfAlarms;
        ExternalEEPROM *eeprom;
    public:
        static const byte START_BYTE = 0xAA;
        static const int START_ADDRESS = 1;
        EEPROMMemoryManager();
        EEPROMMemoryManager(byte state, DayAlarm *alarms, int numberOfAlarms, ExternalEEPROM *eeprom);
        bool writeOnEEPROM();
        bool readOnEEPROM();
        void setState(byte state);
        byte getState();
        void setAlarms(DayAlarm *alarms, int numberOfAlarms);
        DayAlarm* getAlarm(int alarmNumber);
        int getNumberOfAlarms();
        void setExternalEEPROM(ExternalEEPROM *eeprom);
        ExternalEEPROM* getExternalEEPROM();
};

#endif