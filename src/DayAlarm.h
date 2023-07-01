#ifndef DAY_ALARM_H
#define DAY_ALARM_H

#include <Arduino.h>

#include "FullTime.h"

class DayAlarm {
    private:
        byte hours;
        byte minutes;
        int durationInMinutes;
    public:
        DayAlarm();
        DayAlarm(byte hours, byte minutes, int durationInMinutes);
        void setHours(byte hours);
        byte getHours();
        void setMinutes(byte minutes);
        byte getMinutes();
        void setDurationInMinutes(int durationInMinute);
        int getDurationInMinutes();
        bool isActive(FullTime currentTime);
};

#endif