# Body Control Module Features


**Basic Specifications:**
- 8-18v VBAT Compatible
- 5V -> 14.4v 1A Lead acid battery charge circuit over USB-C
- **(OPTIONAL)** Solar panel -> 14.4v charge controller
- Built-in 5v 2A regulator
- 5v -> 3.3v Linear regulator
- 6x VGA Out connectors with common pins
- 5x voltage divider inputs for NTC thermistors

**Board Hardware**
- ESP32 Main board
- SD Card slot over SPI
- 3+ Channel I2C ADC
- Headers for attaching an IMU board on rubber isolators

**Connector pinout**
1. Ground
2. VBAT
3. 5V Supply
4. SCL
5. SDA
6. FL Wheel Speed
7. FR Wheel Speed
8. RL Wheel Speed
9. RR Wheel Speed
10. Engine Oil Temp
11. Engine Head Temp
12. CVT Temp
13. Solar panel input **(?)**
14. Spare TBD
15. Spare TBD