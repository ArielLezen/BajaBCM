#include "Arduino.h"

#include "sensors.cpp"
#include "constants.hpp"

struct Values {

    unsigned int updates;
    unsigned long time;

    // accelerometer information
    float vector[6] {0, 0, 0, 0, 0, 0};     // 

    // gps data if we have that?
    float velocity[3];  // gps data or something?

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

};

namespace calc {

    // declaring variables statically to be used within functions
    // should save on variable declaration overhead?
    float R_THETA = WHEELRADIUS * (TAU / WHEELTEETH);
    float logR = 0.0;

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

    static float* GPSVelocity(Value* curr, Value* prev) {
        return {0.0, 0.0, 0.0}
    }

    static float slippage(&curr) {
        return 0.0
    }


}