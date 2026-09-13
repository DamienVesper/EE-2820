#include "Ultrasound.h"
#include <Wire.h>

Ultrasound::Ultrasound() {
    Wire.begin();
}

uint16_t Ultrasound::getDistance() {
    uint16_t distance = 0;

    Wire.beginTransmission(ULTRASOUND_I2C_ADDR);
    Wire.write(ULTRASOUND_IR_REG);

    if (Wire.endTransmission() == 0) {
        // HiWonder miniAuto ultrasonic sensor returns distance data
        // in millimeters as 16 bits, in big endian.
        Wire.requestFrom(ULTRASOUND_I2C_ADDR, 2);
        if (Wire.available() >= 2) {
            distance = (Wire.read() << 8) | Wire.read();
        }
    }

    return distance;
}

int Ultrasound::avgDistance() {
    int sum = 0;
    for (int i = 0; i < ULTRASOUND_CACHE_SIZE - 1; ++i) {
        this->cache[i] = this->cache[i + 1];
        sum += this->cache[i];
    }

    int current = this->getDistance();

    this->cache[ULTRASOUND_CACHE_SIZE - 1] = current;
    sum += current;

    return (int)(sum / ULTRASOUND_CACHE_SIZE);
}

bool Ultrasound::setRGB(int reg, uint8_t r, uint8_t g, uint8_t b) {
    Wire.beginTransmission(ULTRASOUND_I2C_ADDR);
    Wire.write(reg);

    Wire.write(r);
    Wire.write(g);
    Wire.write(b);

    return Wire.endTransmission();
}

bool Ultrasound::setRGB(uint8_t r, uint8_t g, uint8_t b) {
    return
        this->setRGB(ULTRASOUND_LED_L_REG, r, g, b)
        && this->setRGB(ULTRASOUND_LED_R_REG, r, g, b);
}
