#include "Arduino.h"
#include "../constants.hpp"

class Thermistor {
public:

    int pin;
    int voltage;

    Thermistor(int pin_) {

        pin = pin_;
        pinMode(pin, OUTPUT);

    }

    auto update(Time* time) {
        voltage = analogRead(pin);
        return getTemperature(voltage);
        //return voltage;
    }

private:
    
    float logR;

    float getTemperature(int voltage) {
        logR = log(NOMINAL_RESISTANCE * (1023.0 / (float)voltage - 1)); // this 1023 seems to be some important voltage somewhere but idk what it's deal is
        return 1.0 / (CONST_A*logR*logR*logR + CONST_C*logR + CONST_D);
    }

};