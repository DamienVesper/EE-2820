#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Arduino.h>

/**
 * @brief The I2C address of the ultrasound sensor.
 */
#define ULTRASOUND_I2C_ADDR 0x77
/**
 * @brief The register address of the IR sensor.
 */
#define ULTRASOUND_IR_REG 0x01
/**
 * @brief The register address of the left LED.
 */
#define ULTRASOUND_LED_L_REG 0x02
/**
 * @brief The register address of the right LED.
 */
#define ULTRASOUND_LED_R_REG 0x03
/**
 * @brief The maximum number of distances that can be stored in cache.
 */
#define ULTRASOUND_CACHE_SIZE 3

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
    Ultrasound();

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

#endif
