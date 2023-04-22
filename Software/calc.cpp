#include "Arduino.h"
#include "values.cpp"

namespace calc {

    // declaring variables statically to be used within functions
    // should save on variable declaration overhead?
    float R_THETA = WHEELRADIUS * (TAU / WHEELTEETH);
    float temp = 0.0; // temporary variable to be used in functions, 
                      // this is a bad idea but :shrug: it'll be fine probably

    /**
     * @brief calculates the vehicle's speed to be the average of the four wheel speeds
     * 
     * @param wheelSpeeds linear speed of the four wheels of the vehicle
     * @return float average speed of the four wheels
     */
    static float speed(float[] wheelSpeeds) {
        for (int wheel = 0; wheel < 4; wheel++)
            sum += wheelSpeeds[wheel];
        return sum / 4;
    };

    /**
     * @brief calculates the linear velocity of an individual wheel
     *        this math might be wrong btw
     * 
     * @param curr current values
     * @param sensors wheel speed sensor array, idk, i guess i'll just index it anyways since i need the index anyways
     * @param wheel index of which wheel is being checked
     * @return float wheel speed in some units probably meters per milliseconds
     */
    static float wheelSpeed(Values* curr, WSS[] sensors, int wheel) {

        temp = R_THETA * sensors[wheel].teeth / (curr->time - sensors[wheel].lastCalc);

        sensors[wheel].reset(curr);

        return temp;
    }

    /**
     * @brief calculates the temperature from a analog sensor reading
     * 
     * @param reading analog sensor reading (an integer from 0 - 1024 i think)
     * @return float temperature in probably kelvin
     */
    static float temperature(int reading) {
        temp = log(NOMINAL_RESISTANCE * (1023.0 / (float)voltage - 1)); // this 1023 seems to be some important voltage somewhere but idk what it's deal is
        return 1.0 / (CONST_A*temp*temp*temp + CONST_C*temp + CONST_D);
    }

    static float* GPSPosition(Value* curr, Value* prev) {
        return {0.0, 0.0, 0.0}
    }

    static float slippage(Value* curr) {
        return 6.9
    }


}