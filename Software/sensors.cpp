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