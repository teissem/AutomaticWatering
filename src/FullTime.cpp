#include "FullTime.h"
#include <Arduino.h>

FullTime::FullTime(byte year, byte month, byte day, byte day_of_week, byte hours, byte minutes, byte seconds) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->day_of_week = day_of_week;
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
}

void FullTime::setSeconds(byte seconds) {
    this->seconds = seconds;
}

void FullTime::setMinutes(byte minutes) {
    this->minutes = minutes;
}

void FullTime::setHours(byte hours) {
    this->hours = hours;
}

void FullTime::setDayOfWeek(byte day_of_week) {
    this->day_of_week = day_of_week;
}

void FullTime::setDay(byte day) {
    this->day = day;
}

void FullTime::setMonth(byte month) {
    this->month = month;
}

void FullTime::setYear(byte year) {
    this->year = year;
}

byte FullTime::getSeconds() {
    return this->seconds;
}

byte FullTime::getMinutes() {
    return this->minutes;
}

byte FullTime::getHours() {
    return this->hours;
}

byte FullTime::getDayOfWeek() {
    return this->day_of_week;
}

byte FullTime::getDay() {
    return this->day;
}

byte FullTime::getMonth() {
    return this->month;
}

byte FullTime::getYear() {
    return this->year;
}