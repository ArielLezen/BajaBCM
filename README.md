# Baja BCM Firmware

Go Red Lion Racing!

**Our BCM has the following core functions:**
- Measure vehicle positon, velocity and acceleration
- Measure suspension accelerations
- Measure Oil and CVT Temperatures
- Control the differential, CVT Fan and brake lights
- Provide useful information to the driver
- "Sleep Mode" to turn itself off

**The following sensors are being implemented as of Oct. 15:**
- MPU6050 Accelerometer (Body and Upright Accelerations)
- SN-04 NPN Inductive sensors (Wheel speeds)
- NTC Thermistors (Engine, Oil and CVT Temp)
- Adafruit Ultimate GPS (Absolute positioning @ 10hz)
- Car battery voltage sensor


**Our hardware is as follows:**
- ESP32-WROVER_IE (BCM - 8Mb Builtin memory)
- Lilygo T5 E-ink (Driver interface display with SD Card interface)
