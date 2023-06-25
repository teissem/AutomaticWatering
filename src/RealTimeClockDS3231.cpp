#include "RealTimeClockDS3231.h"

#include <Arduino.h>
#include <Wire.h>

byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}

byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}

RealTimeClockDS3231::RealTimeClockDS3231(int i2c_address) {
    this->i2c_address = i2c_address;
}

FullTime RealTimeClockDS3231::readTime() {
    Wire.beginTransmission(this->i2c_address);
    Wire.write(0);
    Wire.endTransmission();
    Wire.requestFrom(this->i2c_address, 7);
    byte seconds = bcdToDec(Wire.read() & 0x7f);
    byte minutes = bcdToDec(Wire.read());
    byte hours = bcdToDec(Wire.read() & 0x3f);
    byte day_of_week = bcdToDec(Wire.read());
    byte day = bcdToDec(Wire.read());
    byte month = bcdToDec(Wire.read());
    byte year = bcdToDec(Wire.read());
    return FullTime(year, month, day, day_of_week, hours, minutes, seconds);
}


void RealTimeClockDS3231::writeTime(FullTime time) {
    Wire.beginTransmission(this->i2c_address);
    Wire.write(0);
    Wire.write(decToBcd(time.getSeconds()));
    Wire.write(decToBcd(time.getMinutes()));
    Wire.write(decToBcd(time.getHours()));
    Wire.write(decToBcd(time.getDayOfWeek()));
    Wire.write(decToBcd(time.getDay()));
    Wire.write(decToBcd(time.getMonth()));
    Wire.write(decToBcd(time.getYear()));
    Wire.endTransmission();
}