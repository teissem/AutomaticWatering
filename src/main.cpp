#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>

#include "RealTimeClockDS3231.h"
#include "FullTime.h"
#include "AnodeLEDRGB.h"
#include "ColorLEDRGB.h"
#include "DayAlarm.h"

#define RELAY_PIN 26
#define LED_RED_PIN 27
#define LED_GREEN_PIN 12
#define LED_BLUE_PIN 14
#define ALARM_NUMBER 9
#define RTC_I2C_ADDRESS 0x68

// State enumeration
enum AutomaticWateringState {ON, OFF, AUTO};

// Variable definition
BluetoothSerial SerialBT;
AutomaticWateringState state;
RealTimeClockDS3231 rtcDS3231(RTC_I2C_ADDRESS);
AnodeLEDRGB ledRGB(LED_RED_PIN, LED_BLUE_PIN, LED_GREEN_PIN);
DayAlarm alarms[ALARM_NUMBER];
int currentNumberOfAlarms;
bool shouldBeActive;

// Specific functions definition
void printHelp();
void printCurrentTime();
void printAlarms();
void setCurrentTime(String text);
void setAlarm(String text);
void delAlarm(String text);

void setup() {
    // Global Initialization
    Serial.begin(115200);
    SerialBT.begin("AutomaticWatering");
    Wire.begin();
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
    // Variable Initialization
    state = OFF;
    currentNumberOfAlarms = 0;
}

void loop() {
    // Bluetooth management
    if (Serial.available()) {SerialBT.write(Serial.read()); }
    if (SerialBT.available() > 0) {
        String text = SerialBT.readStringUntil('\n');
        text.trim();
        // Command enumeration
        if (text == "HELP") {
            printHelp();
        }
        else if (text == "ON"){ 
            state = ON;
            SerialBT.println("Turn to state ON");
        }
        else if (text == "OFF"){ 
            state = OFF;
            SerialBT.println("Turn to state OFF");
        }
        else if (text == "AUTO") {
            state = AUTO;
            SerialBT.println("Turn to state AUTO");
        }
        else if (text == "GET TIME") {
            printCurrentTime();
        }
        else if (strncmp(text.c_str(), "SET TIME", 8) == 0) {
            setCurrentTime(text);
            printCurrentTime();
        }
        else if (text == "GET ALARMS") {
            printAlarms();
        }
        else if (strncmp(text.c_str(), "SET ALARM", 9) == 0) {
            setAlarm(text);
            printAlarms();
        }
        else if (strncmp(text.c_str(), "DEL ALARM", 9) == 0) {
            delAlarm(text);
            printAlarms();
        }
        else {
            SerialBT.print("Unknown command : ");
            SerialBT.println(text);
            SerialBT.println();
            printHelp();
        }
    }
    // State management
    switch (state)
    {
    case ON:
        ledRGB.turnON(ColorLEDRGB::GREEN);
        digitalWrite(RELAY_PIN, HIGH);
        break;
    case OFF:
        ledRGB.turnON(ColorLEDRGB::RED);
        digitalWrite(RELAY_PIN, LOW);
        break;
    case AUTO:
        shouldBeActive = false;
        ledRGB.turnON(ColorLEDRGB::BLUE);
        for (int i = 0; i < currentNumberOfAlarms; i++) {
            if (alarms[i].isActive(rtcDS3231.readTime())) shouldBeActive = true;
        }
        if (shouldBeActive) digitalWrite(RELAY_PIN, HIGH);
        else digitalWrite(RELAY_PIN, LOW);
        break;
    default:
        break;
    }
}

void printHelp() {
    SerialBT.println("Commands available :");
    SerialBT.println("  ON : Turn to state ON");
    SerialBT.println("  OFF : Turn to state OFF");
    SerialBT.println("  AUTO : Turn to state AUTO");
    SerialBT.println("  SET TIME <TIME>: Set current time on ESP32, format YY/MM/DD HH:MM");
    SerialBT.println("  GET TIME : Get current time on ESP32");
    SerialBT.println("  SET ALARM <TIME>: Set an alarm, format HH:MM mmm");
    SerialBT.println("  DEL ALARM <NUMBER>: Delete an alarm");
    SerialBT.println("  GET ALARMS : Get alarms programmed");
    SerialBT.println("  HELP : Show available commands");
}

void printCurrentTime() {
    FullTime currentTime = rtcDS3231.readTime();
    SerialBT.print("Current time : ");
    SerialBT.print(currentTime.getYear());
    SerialBT.print("/");
    SerialBT.print(currentTime.getMonth());
    SerialBT.print("/");
    SerialBT.print(currentTime.getDay());
    SerialBT.print(" ");
    SerialBT.print(currentTime.getHours());
    SerialBT.print(":");
    SerialBT.print(currentTime.getMinutes());
    SerialBT.print(":");
    SerialBT.println(currentTime.getSeconds());
}

void printAlarms() {
    if (currentNumberOfAlarms == 0) {
        SerialBT.println("No alarms found.");
    }
    else {
        SerialBT.print("Showing ");
        SerialBT.print(currentNumberOfAlarms);
        SerialBT.println(" alarms :");
        for (int i = 0; i < currentNumberOfAlarms; i++) {
            SerialBT.print("  ");
            SerialBT.print(i+1);
            SerialBT.print(" --> ");
            SerialBT.print(alarms[i].getHours());
            SerialBT.print(":");
            SerialBT.print(alarms[i].getMinutes());
            SerialBT.print(", during ");
            SerialBT.print(alarms[i].getDurationInMinutes());
            SerialBT.println(" minutes.");
        }
    }
}

void setCurrentTime(String text) {
    // Get current time
    char tenYearChar = text.charAt(9);
    char unitYearChar = text.charAt(10);
    char tenMonthChar = text.charAt(12);
    char unitMonthChar = text.charAt(13);
    char tenDayChar = text.charAt(15);
    char unitDayChar = text.charAt(16);
    char tenHourChar = text.charAt(18);
    char unitHourChar = text.charAt(19);
    char tenMinuteChar = text.charAt(21);
    char unitMinuteChar = text.charAt(22);
    // Convert to byte
    byte tenYear = (byte) ((tenYearChar - '0')*10);
    byte unitYear = (byte) unitYearChar - '0';
    byte tenMonth = (byte) ((tenMonthChar - '0')*10);
    byte unitMonth = (byte) unitMonthChar - '0';
    byte tenDay = (byte) ((tenDayChar - '0')*10);
    byte unitDay = (byte) unitDayChar - '0';
    byte tenHour = (byte) ((tenHourChar - '0')*10);
    byte unitHour = (byte) unitHourChar - '0';
    byte tenMinute = (byte) ((tenMinuteChar - '0')*10);
    byte unitMinute = (byte) unitMinuteChar - '0';
    // Set time
    FullTime current_time(tenYear+unitYear, tenMonth+unitMonth, tenDay+unitDay, 1, tenHour+unitHour, tenMinute+unitMinute, 0);
    rtcDS3231.writeTime(current_time);
}

void setAlarm(String text) {
    // Get alarm
    char tenHourChar = text.charAt(10);
    char unitHourChar = text.charAt(11);
    char tenMinuteChar = text.charAt(13);
    char unitMinuteChar = text.charAt(14);
    char hundredDuringMinutesChar = text.charAt(16);
    char tenDuringMinutesChar = text.charAt(17);
    char unitDuringMinutesChar = text.charAt(18);
    // Convert to byte
    byte tenHour = (byte) ((tenHourChar - '0')*10);
    byte unitHour = (byte) unitHourChar - '0';
    byte tenMinute = (byte) ((tenMinuteChar - '0')*10);
    byte unitMinute = (byte) unitMinuteChar - '0';
    // Convert to int
    int hundredDuringMinutes = (hundredDuringMinutesChar - '0') * 100;
    int tenDuringMinutes = (tenDuringMinutesChar - '0') * 10;
    int unitDuringMinutes = unitDuringMinutesChar - '0';
    // Set Alarm
    alarms[currentNumberOfAlarms] = DayAlarm(tenHour+unitHour, tenMinute+unitMinute, hundredDuringMinutes+tenDuringMinutes+unitDuringMinutes);
    currentNumberOfAlarms++;
}

void delAlarm(String text) {
    // Get alarm number
    char alarmNumberChar = text.charAt(10);
    int alarmNumber = alarmNumberChar - '0' - 1;
    // Delete alarm and reorganize
    if (alarmNumber >= currentNumberOfAlarms || alarmNumber < 0) return;
    for (int i = alarmNumber; i < currentNumberOfAlarms; i++) {
        alarms[i] = alarms[i + 1];
    }
    currentNumberOfAlarms--;
}