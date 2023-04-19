#include "Arduino.h"

class Thermometer {
public:

    int pin;
    int temperature;

    Thermometer(int pin_) {
        pin = pin_;
    }

    int update() {
        temperature = analogRead(pin);
        return temperature;
    }

};