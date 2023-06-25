#ifndef REAL_TIME_CLOCK_DS3231_H
#define REAL_TIME_CLOCK_DS3231_H

#include "FullTime.h"

class RealTimeClockDS3231 {
    private:
        int i2c_address;
    public:
        RealTimeClockDS3231(int i2c_address);
        FullTime readTime();
        void writeTime(FullTime time);
};

#endif