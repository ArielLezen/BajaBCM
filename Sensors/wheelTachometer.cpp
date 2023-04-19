#include "Arduino.h"
#include "wheelTachometer.hpp"

float R_THETA = WHEELRADIUS * (TAU / WHEELTEETH);

class WheelTachometer {

public:

    int pin[4];
    int curr[4] {0, 0, 0, 0}; // current reading
    int prev[4] {0, 0, 0, 0}; // previous reading

    int lastPush[4] {0, 0, 0, 0}; // time since it was toggled on
    float velocity[4] {0.0, 0.0, 0.0, 0.0};

    WheelTachometer(int frontRight, int frontLeft, int backRight, int backLeft) {
        pin[FR_L] = frontLeft;
        pin[FR_R] = frontRight;
        pin[BA_L] = backLeft;
        pin[BA_R] = backRight;
    }

    /**
     * @brief Reads the wheel tachometers
     * 
     * @param time 
     * @return int* current wheel reading
     */
    int* update(Time* time) {

        curr[FR_L] = digitalRead(pin[FR_L]);
        curr[FR_R] = digitalRead(pin[FR_R]);
        curr[BA_L] = digitalRead(pin[BA_L]);
        curr[BA_R] = digitalRead(pin[BA_R]);

        return calculate(time);
    };

private:

    /**
     * @brief Runs logic on read inputs each update
     * 
     * @param time 
     * @return int* 
     */
    int* calculate(Time* time) {

        for (unsigned int wheel = 0; wheel != 4; wheel++) {
            
            if (!prev[wheel] && curr[wheel]) { // toggled on
                lastPush[wheel] = time->curr - lastPush[wheel];
            }
            calcSpeed(wheel);

        }

        return lateUpdate(time);

    }


    /**
     * @brief cleanup for next update happens here,
     *        saving current values to be used next loop
     * 
     * @param time 
     * @return int* current wheel reading
     */
    int* lateUpdate(Time* time) {
        
        // saving reading
        prev[FR_L] = curr[FR_L];
        prev[FR_R] = curr[FR_R];
        prev[BA_L] = curr[BA_L];
        prev[BA_R] = curr[BA_R];

        return curr;
    };

    void calcSpeed(int wheel) {

        velocity[wheel] = R_THETA / lastPush[wheel];

    };

};