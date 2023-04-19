#include "Arduino.h"
#include "pins.h"

#include "Sensors/accelerometer.cpp"
#include "Sensors/wheelTachometer.cpp"
#include "Sensors/thermistor.cpp"

struct Time {
    unsigned long curr;     // time of current update
    unsigned long last;     // time of previous update
    int delta;              // time since previous update
    unsigned int updates;   // total amount of updates, so we don't need to update some things every loop
    Time(unsigned long startTime = 0) {
        curr = startTime;
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

Thermistor thermCVT;
Thermistor thermEngine;
Thermistor thermTrans;

WheelTachometer wheels;

Accelerometer accel;

void setup() {

    // Thermometers
    thermCVT = Thermistor(CVTTHERM_PIN);
    thermEngine = Thermistor(ENGTHERM_PIN);
    thermTrans = Thermistor(TRANSTHERM_PIN);

    // Wheel Speed
    wheels = WheelTachometer(WSSFL_PIN, WSSFR_PIN, WSSRL_PIN, WSSRR_PIN);

    // Accelerometer
    accel = Accelerometer(PLACEHOLDER);

    // time starts
    time = Time();

    // Initalize communication
    Serial.begin(BAUD);

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
