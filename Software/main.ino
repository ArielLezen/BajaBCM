#include <utility>

#include "Arduino.h"
#include "pins.h"


#include "sensors.cpp"
#include "values.cpp"
#include "calc.cpp"

#include "constants.hpp"

void setup() {

    Values curr = new Values();
    Values prev = new Values();
    //Values delta = new Values(); // might not be used but is here idk?

    // Thermometers
    SimpleSensor thermCVT = AnalogSensor(CVTTHERM_PIN);
    SimpleSensor thermEngine = AnalogSensor(ENGTHERM_PIN);
    SimpleSensor thermTrans = AnalogSensor(TRANSTHERM_PIN);

    // Wheel Speed
    WSS wheelSensors[4] = {
        WSS(WSSFL_PIN),   // front left wheel
        WSS(WSSFR_PIN),   // front right wheel
        WSS(WSSRL_PIN),   // back left wheel
        WSS(WSSRR_PIN)    // back right wheel
    };


    // Accelerometer
    Accelerometer accel = Accelerometer(0, 0, 0, 0, 0, 0); // placeholder values

    // Initalize communication
    Serial.begin(BAUD);

};

void loop() {

    updateValues();

    calculateThings();

    logData();

    saveValues();

};

/**
 * @brief this is where current values are read from the sensors
 * 
 */
void updateValues() {
    
    curr.update(); // this only updates time

    // don't check thermistors every update
    if (update % 6 = 0) { thermCVT.update(); }
    if (update % 6 = 2) { thermEngine.update(); }
    if (update % 6 = 4) { thermTrans.update(); }
    
    accel.update();
    
}

/**
 * @brief this is where we update the calculated values
 * 
 */
void calculateThings() {

    curr.vector = accel.vector;
    
    curr.position = calc::GPSPosition(&curr, &prev)

    for (int wheel = 0; wheel < 4; wheel++) {
        if (wheelSensors[wheel].teeth >= WSS.COUNTER_THRESHOLD){
            curr.wheelVelocity[wheel] = calc::wheelSpeed(curr, wheelSensors, wheel);
            curr.slippage[wheel] = calc::slippage(&curr);
        }
    }
    curr.vehicleSpeed = calc::speed(&curr); // overall vehicle speed
    
    // setting these every time since that's probably faster than checking if they got updated
    curr.tempCVT = calc::temperature(thermCVT.value);
    curr.tempEngine = calc::temperature(thermEngine.value);
    curr.tempTrans = calc::temperature(thermTrans.value);

}

/**
 * @brief save data
 * 
 */
*/
void logData() {
    Serial.println(curr.toString());
}

/**
 * @brief this is where current values are saved for the next loop
 * 
 */
void savePrev() {
    std::swap(&curr, &prev);
}