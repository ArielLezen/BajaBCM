#include "Arduino.h"
#include <string>

#include "sensors.cpp"
#include "constants.hpp"

struct Values {

    unsigned int updates;
    unsigned long time;

    // accelerometer information
    float vector[6] {0, 0, 0, 0, 0, 0};     // 

    // gps data if we have that?
    float position[3];  // gps data or something?

    // wheel speed sensor information
    int wheelData[4] {0, 0, 0, 0};          // sensor output
    float wheelVelocity[4] {0, 0, 0, 0};    // wheel velocities
    float vehicleSpeed;                     // vehicle speed calculated from wheel velocities

    // thermistors
    float tempCVT;                          // temperature of CVT in Kelvins
    float tempEngine;                       // temperature of engine in Kelvins
    float tempTrans;                        // temperature of transmission in Kelvins

    // wheel slip
    float slippage[4] {0, 0, 0, 0};         // % each of the wheels is slipping

    void update() {
        time = millis();
        updates = updates + 1;
    }

    /**
     * @brief some sort of print method, idk how we are
     * going to end up logging but i guess this is a start
     * 
     * @return string 
     */
    string toString() {
        return std::format( // i have no idea if this is going to work properly
            "Update {} at {}ms\n"
            "Accelerometer : [{}, {}, {}, {}, {}, {}]\n"
            "GPS : [{}, {}, {}]\n"
            "Vehicle Speed : {}\n"
            "lastPush : [{}, {}, {}, {}]\n"
            "Wheel Velocity : [{}, {}, {}, {}]\n"
            "Wheel Slip : [{}, {}, {}, {}]\n"
            "Temperatures :\t\tCVT {}\t\tEngine {}\t\tTransmission {}\n"
            updates, time,
            vector[0], vector[1], vector[2], vector[3], vector[4], vector[5],
            position[0], position[1], position[2],
            vehicleSpeed,
            lastPush[0], lastPush[1], lastPush[2], lastPush[3],
            wheelVelocity[0], wheelVelocity[1], wheelVelocity[2], wheelVelocity[3],
            slippage[0], slippage[1], slippage[2], slippage[3],
            tempCVT, tempEngine, tempTrans
            )
    }

};
