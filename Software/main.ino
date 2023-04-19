#include "Arduino.h"
#include "pins.h"

#include "Sensors/accelerometer.cpp"
#include "Sensors/tachometer.cpp"
#include "Sensors/thermometer.cpp"

struct Time {
    
    unsigned long curr = 0;
    unsigned long last;
    int delta;
    
    Time() {
        update();
    };

    void update() {
        last = curr;
        curr = millis();
        delta = curr - last; // millis() rolls over after like a month and i think you'll have bigger problems if the car is constantly running that whole time
    }

};

Time time;

Accelerometer thermCVT;
Accelerometer thermEngine;
Accelerometer thermTrans;

Tachometer wheels;

Accelerometer accel;

void setup() {

    // Thermometers
    thermCVT = Accelerometer(CVTTHERM_PIN);
    thermEngine = Accelerometer(ENGTHERM_PIN);
    thermTrans = Accelerometer(TRANSTHERM_PIN);

    // Wheel Speed
    wheels = Tachometer(WSSFL_PIN, WSSFR_PIN, WSSRL_PIN, WSSRR_PIN);

    // Accelerometer
    accel = Accelerometer(PLACEHOLDER);

    // time starts
    time = Time();

};

void loop() {

    time.update();

    // Time
    Serial.println(time.curr);

    // Thermometers
    Serial.println(thermCVT.update(&time));
    Serial.println(thermEngine.update(&time));
    Serial.println(thermTrans.update(&time));

    // Wheel Speed
    Serial.println(wheels.update(&time));
    
    // Accelerometer
    Serial.println(accel.update(&time));
    
};
