#include <Arduino.h>
#include <Wire.h>

#include "Config.h"
#include "Ultrasound.h"

uint16_t Ultrasound::getDistance() {

    Wire.beginTransmission(Sensors::US_ADDR);
    Wire.write(Sensors::US_DIST_REG);

    if (Wire.endTransmission() == 0) {
        // HiWonder miniAuto ultrasonic sensor returns distance data
        // in millimeters as 16 bits, in big endian.
        Wire.requestFrom(Sensors::US_ADDR, (uint8_t)2);
        if (Wire.available() >= 2) {
            distance = (Wire.read() << 8) | Wire.read();
        }
    }

    return distance;
}

int Ultrasound::avgDistance() {
    int sum = 0;
    for (int i = 0; i < Sensors::US_CACHE_SIZE - 1; ++i) {
        this->cache[i] = this->cache[i + 1];
        sum += this->cache[i];
    }

    int current = this->getDistance();

    this->cache[Sensors::US_CACHE_SIZE - 1] = current;
    sum += current;

    return (int)(sum / Sensors::US_CACHE_SIZE);
}

bool Ultrasound::setRGB(int reg, uint8_t r, uint8_t g, uint8_t b) {
    Wire.beginTransmission(Sensors::US_ADDR);
    Wire.write(reg);

    Wire.write(r);
    Wire.write(g);
    Wire.write(b);

    return Wire.endTransmission();
}

bool Ultrasound::setRGB(uint8_t r, uint8_t g, uint8_t b) {
    return
        this->setRGB(Sensors::US_LEDL_REG, r, g, b)
        && this->setRGB(Sensors::US_LEDR_REG, r, g, b);
}
