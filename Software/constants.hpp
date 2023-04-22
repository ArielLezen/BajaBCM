/*
    GENERAL CONSTANTS
*/

#define BAUD 9600 // Serial communication rate in bits per second

/*
    ACCELEROMETER CONSTANTS
*/

// nothing yet

/*
    THERMISTOR CONSTANTS
*/

#define NOMINAL_RESISTANCE 10000.0  // Nominal resistance at 25⁰C, needs to be double checked for our thermistor
#define CONST_A 2.019202697e-07     // Constant used in voltage to temperature converison
#define CONST_C 2.378405444e-04     // Constant used in voltage to temperature converison
#define CONST_D 1.009249522e-03     // Constant used in voltage to temperature converison

/*
    WHEEL CONSTANTS
*/

// Wheel pin indices
#define FR_L 0      // Array index for front left wheel
#define FR_R 1      // Array index for front right wheel
#define BA_L 2      // Array index for back left wheel
#define BA_R 3      // Array index for back right wheel

// Constants for calculations
#define WHEELRADIUS 6.9         // Outer radius of the wheel in meters
#define TAU 6.283185307179586   // Circle constant (the better one)
#define WHEELTEETH 10           // Amount of pegs on the wheel that the sensor reads

