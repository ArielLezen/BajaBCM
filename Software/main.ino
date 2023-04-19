#include "Arduino.h"
#include "pins.h"

#include "Sensors/accelerometer.cpp"
#include "Sensors/tachometer.cpp"
#include "Sensors/thermometer.cpp"

struct Time {
    unsigned long curr;     // time of current update
    unsigned long last;     // time of previous update
    int delta;              // time since previous update
    int updates;            // total amount of updates
    Time() {
        curr = 0;
        update();
    };
    void update() {
        last = curr;
        curr = millis();
        delta = curr - last; // millis() rolls over after like a month and i think you'll have bigger problems if the car is constantly running that whole time
        updates++;
    };
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
