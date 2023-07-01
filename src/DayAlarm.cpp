#include "DayAlarm.h"

DayAlarm::DayAlarm() {
    this->hours = 0;
    this->minutes = 0;
    this->durationInMinutes = -1;
}

DayAlarm::DayAlarm(byte hours, byte minutes, int durationInMinutes) {
    this->hours = hours;
    this->minutes = minutes;
    this->durationInMinutes = durationInMinutes;
}

void DayAlarm::setHours(byte hours) {
    this->hours = hours;
}

byte DayAlarm::getHours() {
    return this->hours;
}

void DayAlarm::setMinutes(byte minutes) {
    this->minutes = minutes;
}

byte DayAlarm::getMinutes() {
    return this->minutes;
}

void DayAlarm::setDurationInMinutes(int durationInMinutes) {
    this->durationInMinutes = durationInMinutes;
}

int DayAlarm::getDurationInMinutes() {
    return this->durationInMinutes;
}

bool DayAlarm::isActive(FullTime currentTime) {
    if (this->durationInMinutes < 0) {
        return false;
    }
    byte currentHours = currentTime.getHours();
    byte currentMinutes = currentTime.getMinutes();
    int currentMinutesCumulated = ((int) currentHours) * 60 + ((int) currentMinutes);
    int startAlarmMinutesCumulated = ((int) this->hours) * 60 + ((int) this->minutes);
    int stopAlarmMinutesCumulated = startAlarmMinutesCumulated + this->durationInMinutes;
    // Cas nominal
    if (stopAlarmMinutesCumulated < 24 * 60) {
        return (currentMinutesCumulated >= startAlarmMinutesCumulated) && (currentMinutesCumulated <= stopAlarmMinutesCumulated);
    }
    // Cas particulier si on passe minuit
    else {
        return (currentMinutesCumulated >= startAlarmMinutesCumulated) || (currentMinutesCumulated + 24*60 <= stopAlarmMinutesCumulated); 
    }
}