#include "Arduino.h"
#include "pins.h"

#include "Sensors/accelerometer.cpp"
#include "Sensors/tachometer.cpp"
#include "Sensors/thermometer.cpp"

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

};

void loop() {

    // Thermometers
    Serial.println(thermCVT.update());
    Serial.println(thermEngine.update());
    Serial.println(thermTrans.update());

    // Wheel Speed
    Serial.println(wheels.update());
    
    // Accelerometer
    Serial.println(accel.update());
    
};