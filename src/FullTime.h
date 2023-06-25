#ifndef FULL_TIME_H
#define FULL_TIME_H

#include <Arduino.h>

class FullTime{
    private:
        byte seconds;
        byte minutes;
        byte hours;
        byte day_of_week;
        byte day;
        byte month;
        byte year;
    public:
        FullTime(byte year, byte month, byte day, byte day_of_week, byte hours, byte minutes, byte seconds);
        void setSeconds(byte seconds);
        void setMinutes(byte minutes);
        void setHours(byte hours);
        void setDayOfWeek(byte day_of_week);
        void setDay(byte day);
        void setMonth(byte month);
        void setYear(byte year);
        byte getSeconds();
        byte getMinutes();
        byte getHours();
        byte getDayOfWeek();
        byte getDay();
        byte getMonth();
        byte getYear();
};

#endif