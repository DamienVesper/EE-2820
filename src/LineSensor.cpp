#include "LineSensor.h"
#include <Wire.h>

bool LineSensor::update() {
    Wire.beginTransmission(LINE_SENSOR_I2C_ADDR);
    Wire.write(LINE_SENSOR_REG);

    if (Wire.endTransmission() != 0) return false;

    Wire.requestFrom(LINE_SENSOR_I2C_ADDR, 1);
    if (Wire.available() >= 1) {
        uint8_t data = Wire.read();

        ch1 = data & 1;
        ch2 = (data >> 1) & 1;
        ch3 = (data >> 2) & 1;
        ch4 = (data >> 3) & 1;

        return true;
    }

    return false;
}
