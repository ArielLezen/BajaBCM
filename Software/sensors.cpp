#include "Arduino.h"

#include "constants.hpp"

struct SimpleSensor {

    int value;

    SimpleSensor (int p) {
        pin = p;
    }

    void virtual update() = 0;

};

struct AnalogSensor : public SimpleSensor {

    void update() {
        value = analogRead(pin);
    }

};

struct DigitalSensor : public SimpleSensor {

    void update() {
        value = digitalRead(pin);
    }

};

struct Accelerometer {

    int pins[6] {0, 0, 0, 0, 0, 0}
    float vector[6] {0, 0, 0, 0, 0, 0};

    Accelerometer(int x, int y, int z, int pitch, int yaw, int roll) {
        pins = {x, y, z, pitch, yaw, z}
    }

    void update() {
        vector = {0, 0, 0, 0, 0, 0}
    }

}

struct WSS {

    int pin;
    int teeth;
    unsigned long lastCalc;

    static int COUNTER_THRESHOLD = 3;

    WSS(int pin_) {
        pin = pin_;
        teeth = 0;
        lastCalc = 0;

        attachInterruptArg(pin, (void (*)(void*))ISR, NULL, CHANGE); // this might not work, not sure if it needs to be a standalone function of if the method i made works fine
    }

    // this might not work, i'm not sure how this function was supposed to be
    void IRAM_ATTR ISR() {
        teeth++;
    }

    int reset(Values* curr) {
        teeth = 0;
        lastCalc = curr->time;
    }

}