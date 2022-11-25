# Body Control Module Features


**Basic Specifications:**
- 8-18v VBAT Compatible
- 5V -> 14.4v 1A Lead acid battery charge circuit over USB-C
- **(OPTIONAL)** Solar panel -> 14.4v charge controller
- Built-in 5v 2A regulator
- 3x Thermistor inputs
- RPM and Wheel Speed sensing

**Board Hardware**
- Headers for ESP32 Daughter board
- Headers for attaching an I2C IMU board
- Four high current outputs:
- Front Dif. Control
- Headlight Control
- Brake Light Control

**Connector schema**
1. RJ45 for wheel speed and GPS sensors
2. RJ12 for RPM and thermistor sensors
3. TBD For high current accessories

**ESP32 Pin Map**
 - TX - TX (35)
 - RX - RX (34)
 - RL - G34
 - RR - G35
 - FL - G32
 - FR - G33
 - CAR_BAT - G25
 - CVT_TEMP - G26
 - ENG_TEMP - G27
 - TRANS_TEMP - G14
 - INT_ACC - G19
