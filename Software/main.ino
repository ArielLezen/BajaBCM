#include <utility>

#include "Arduino.h"
#include "pins.h"

#include "sensors.cpp"
#include "values.cpp"

#include "constants.hpp"

void setup() {

    Values curr = new Values();
    Values prev = new Values();
    //Values delta = new Values() // might not be used but is here idk?

    // Thermometers
    SimpleSensor thermCVT = AnalogSensor(CVTTHERM_PIN);
    SimpleSensor thermEngine = AnalogSensor(ENGTHERM_PIN);
    SimpleSensor thermTrans = AnalogSensor(TRANSTHERM_PIN);

    // Wheel Speed
    SimpleSensor wheelSensors[4] = {
        DigitalSensor(WSSFL_PIN),   // front left wheel
        DigitalSensor(WSSFR_PIN),   // front right wheel
        DigitalSensor(WSSRL_PIN),   // back left wheel
        DigitalSensor(WSSRR_PIN)    // back right wheel
    };

    // Accelerometer
    Accelerometer accel = Accelerometer(0, 0, 0, 0, 0, 0); // placeholder values

    // Initalize communication
    Serial.begin(BAUD);

};

void loop() {

    updateValues();

    calculateThings();

    saveValues();

};

/**
 * @brief this is where current values are read from the sensors
 * 
 */
void updateValues() {
    
    curr.update(); // this only updates time

    thermCVT.update();
    thermEngine.update();
    thermTrans.update();
    
    for (int i = 0; i < 4; i++) {
        wheelSensors[i].update()
    }

    accel.update();
    
}

/**
 * @brief this is where we update the calculated values
 * 
 */
void calculateThings() {

    curr.vector = accel.vector;
    
    curr.velocity = calc::GPSVelocity(&curr, &prev)

    for (int wheel = 0; wheel < 4; wheel++) {
        if (prev.wheelData[wheel] == LOW && curr.wheelData[wheel]) { // only updates wheel speeds if it reads a pin since the delta is otherwise unknown
            curr.lastPush[wheel] = curr.time;

            curr.wheelVelocity[wheel] = calc::wheelSpeed(curr.lastPush[wheel], prev.lastPush[wheel])
            
            curr.slippage[wheel] = calc::slippage(&curr)
        }
    }
    curr.vehicleSpeed = calc::speed(&curr); // overall vehicle speed
    
    curr.tempCVT = calc::temperature(thermCVT.value);
    curr.tempEngine = calc::temperature(thermEngine.value);
    curr.tempTrans = calc::temperature(thermTrans.value);

}

/**
 * @brief this is where current values are saved for the next loop
 * 
 */
void savePrev() {
    std::swap(&curr, &prev);
}