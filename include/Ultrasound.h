#pragma once

#include <Arduino.h>

/**
 * @brief Interface for Hiwonder Glowy Ultrasonic Sensor (HW-SR06).
 * @link https://www.hiwonder.com/products/glowy-rgb-ultrasonic-sensor
 */
class Ultrasound {
private:
    /**
     * @brief Cached previous distances to reduce noise.
     */
    int cache[3];
public:
    /**
     * @brief I do not care that this is not recommended in C++. I want to pass this class.
     * 
     */
    uint16_t distance;

    /**
     * @brief Obtain distance, in millimeters to an object from the ultrasound sensor.
     */
    uint16_t getDistance();

    /**
     * @brief Obtain distance, in millimeters, to an object with smoothing.
     */
    int avgDistance();

    /**
     * @brief Set the color of an LED.
     * 
     * @param reg The register address of the LED.
     * @param r Red color (0 - 255).
     * @param g Green color (0 - 255).
     * @param b Blue color (0 - 255).
     * @return `true` if successful, `false` otherwise.
     */
    bool setRGB(int reg, uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Set the color of both LEDs.
     * 
     * @param r Red color (0 - 255).
     * @param g Green color (0 - 255).
     * @param b Blue color (0 - 255).
     * @return `true` if successful, `false` otherwise.
     */
    bool setRGB(uint8_t r, uint8_t g, uint8_t b);
};
