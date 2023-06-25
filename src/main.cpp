#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>

#include "RealTimeClockDS3231.h"
#include "FullTime.h"
#include "AnodeLEDRGB.h"
#include "ColorLEDRGB.h"

#define RELAY_PIN 26
#define LED_RED_PIN 27
#define LED_GREEN_PIN 12
#define LED_BLUE_PIN 14
#define RTC_I2C_ADDRESS 0x68

// State enumeration
enum AutomaticWateringState {ON, OFF, AUTO};

// Variable definition
BluetoothSerial SerialBT;
AutomaticWateringState state;
RealTimeClockDS3231 rtcDS3231(RTC_I2C_ADDRESS);
AnodeLEDRGB ledRGB(LED_RED_PIN, LED_BLUE_PIN, LED_GREEN_PIN);

void printHelp();
void printCurrentTime();
void setCurrentTime(String text);

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
}

void loop() {
    // Bluetooth management
    if (Serial.available()) {SerialBT.write(Serial.read()); }
    if (SerialBT.available() > 0) {
        String text = SerialBT.readStringUntil('\n');
        text.trim();
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
        else if (text == "GET TIME") {
            printCurrentTime();
        }
        else if (strncmp(text.c_str(), "SET TIME", 8) == 0) {
            setCurrentTime(text);
            printCurrentTime();
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
    default:
        break;
    }
}

void printHelp() {
    SerialBT.println("Commands available :");
    SerialBT.println("  ON : Turn ON");
    SerialBT.println("  OFF : Turn OFF");
    SerialBT.println("  SET TIME <TIME>: Set current time on ESP32, format YY/MM/DD HH:MM");
    SerialBT.println("  GET TIME : Get current time on ESP32");
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

