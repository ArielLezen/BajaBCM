#include "Arduino.h"

class Accelerometer {
public:

    int pin;
    int vector; // placeholder

    Accelerometer(int pin_) {
        pin = pin_;
    }

    int update(Time* time) {
        vector = analogRead(pin);
        return vector;
    }

};