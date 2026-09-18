#include "LineSensor.h"
#include <Wire.h>

bool LineSensor::update() {
    Wire.beginTransmission(LINE_SENSOR_I2C_ADDR);
    Wire.write(LINE_SENSOR_REG);

    if (Wire.endTransmission() != 0) return false;

    Wire.requestFrom(LINE_SENSOR_I2C_ADDR, 1);
    if (Wire.available() >= 1) {
        uint8_t data = Wire.read();

        ch1 = data & 0x01;
        ch2 = (data >> 1) & 0x01;
        ch3 = (data >> 2) & 0x01;
        ch4 = (data >> 3) & 0x01;

        return true;
    }

    return false;
}
