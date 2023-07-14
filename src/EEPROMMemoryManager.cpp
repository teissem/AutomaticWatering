#include "EEPROMMemoryManager.h"

EEPROMMemoryManager::EEPROMMemoryManager() {
    this->state = -1;
    this->alarms = NULL;
    this->numberOfAlarms = -1;
    this->eeprom = NULL;
}

EEPROMMemoryManager::EEPROMMemoryManager(byte state, DayAlarm *alarms, int numberOfAlarms, ExternalEEPROM *eeprom) {
    this->state = state;
    this->alarms = alarms;
    this->numberOfAlarms = numberOfAlarms;
    this->eeprom = eeprom;
}

bool EEPROMMemoryManager::writeOnEEPROM() {
    if (this->state == -1 || this->alarms == NULL || this->numberOfAlarms == -1 || this->eeprom == NULL) {
        return false;
    }
    int address = EEPROMMemoryManager::START_ADDRESS;
    // Start Byte
    this->eeprom->write8bit(address, EEPROMMemoryManager::START_BYTE);
    address++;
    // State
    this->eeprom->write8bit(address, this->state);
    address++;
    // Number of alarms
    this->eeprom->write8bit(address, this->numberOfAlarms);
    address++;
    // Alarms
    for (int i = 0; i < this->numberOfAlarms; i++) {
        this->eeprom->write8bit(address, this->alarms[i].getHours());
        address++;
        this->eeprom->write8bit(address, this->alarms[i].getMinutes());
        address++;
        this->eeprom->writeInt(address, this->alarms[i].getDurationInMinutes());
        address += 4;
    }
    return true;
}

bool EEPROMMemoryManager::readOnEEPROM() {
    if (this->eeprom == NULL) {
        return false;
    }
    // Get start byte
    int address = EEPROMMemoryManager::START_ADDRESS;
    if (this->eeprom->read8bit(address) != EEPROMMemoryManager::START_BYTE) {
        return false;
    }
    address++;
    // Get state
    this->state = this->eeprom->read8bit(address);
    address++;
    // Get number of alarms
    this->numberOfAlarms = this->eeprom->read8bit(address);
    address++;
    // Get alarms
    for (int i = 0; i < this->numberOfAlarms; i++){
        this->alarms[i].setHours(this->eeprom->read8bit(address));
        address++;
        this->alarms[i].setMinutes(this->eeprom->read8bit(address));
        address++;
        this->alarms[i].setDurationInMinutes(this->eeprom->readInt(address));
        address += 4;
    }
    return true;
}

void EEPROMMemoryManager::setState(byte state) {
    this->state = state;
}

byte EEPROMMemoryManager::getState() {
    return this->state;
}

void EEPROMMemoryManager::setAlarms(DayAlarm *alarms, int numberOfAlarms) {
    this->alarms = alarms;
    this->numberOfAlarms = numberOfAlarms;
}

DayAlarm* EEPROMMemoryManager::getAlarm(int alarmNumber) {
    return &(this->alarms[alarmNumber]);
}

int EEPROMMemoryManager::getNumberOfAlarms() {
    return this->numberOfAlarms;
}

void EEPROMMemoryManager::setExternalEEPROM(ExternalEEPROM *eeprom) {
    this->eeprom = eeprom;
}

ExternalEEPROM* EEPROMMemoryManager::getExternalEEPROM() {
    return this->eeprom;
}
