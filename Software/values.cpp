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
    int lastPush[4] {0, 0, 0, 0};           // time since of wheel tach toggle on
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

namespace calc {

    // declaring variables statically to be used within functions
    // should save on variable declaration overhead?
    float R_THETA = WHEELRADIUS * (TAU / WHEELTEETH);
    float logR = 0.0;

    /**
     * @brief calculates the vehicle's speed to be the average of the four wheel speeds
     * 
     * @param wheelSpeeds 
     * @return float 
     */
    static float speed(float[] wheelSpeeds) {
        for (int wheel = 0; wheel < 4; wheel++)
            sum += wheelSpeeds[wheel];
        return sum / 4;
    };

    static float wheelSpeed(int currTime, int prevTime) {
        return R_THETA / (currTime - prevTime);
    }

    static float temperature(int reading) {
        logR = log(NOMINAL_RESISTANCE * (1023.0 / (float)voltage - 1)); // this 1023 seems to be some important voltage somewhere but idk what it's deal is
        return 1.0 / (CONST_A*logR*logR*logR + CONST_C*logR + CONST_D);
    }

    static float* GPSPosition(Value* curr, Value* prev) {
        return {0.0, 0.0, 0.0}
    }

    static float slippage(&curr) {
        return 0.0
    }


}