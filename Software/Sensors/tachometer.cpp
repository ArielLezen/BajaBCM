#include "Arduino.h"
#include "tachometer.hpp"

class Tachometer {

public:

    int pin[4];
    int reading[4];

    float speed;

    Tachometer(int frontRight, int frontLeft, int backRight, int backLeft) {
        pin[FRONTLEFT] = frontLeft;
        pin[FRONTRIGHT] = frontRight;
        pin[BACKRIGHT] = backRight;
        pin[BACKLEFT] = backLeft;
    }

    int* update(Time* time) {

        reading[FRONTLEFT] = digitalRead(pin[FRONTLEFT]);
        reading[BACKRIGHT] = digitalRead(pin[BACKRIGHT]);
        reading[FRONTRIGHT] = digitalRead(pin[FRONTRIGHT]);
        reading[BACKLEFT] = digitalRead(pin[BACKLEFT]);

        return reading;

    };

private:

    void calcSpeed() {

        speed = 69; // placeholder

    };

};