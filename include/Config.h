#pragma once

#include <Arduino.h>

namespace Drivetrain {
    constexpr float CENTER_DIST = 91.44f;
}

namespace Pins {
    constexpr uint8_t MOTOR_PWM[4] = {10, 9, 6, 11};
    constexpr uint8_t MOTOR_DIR[4] = {12, 8, 7, 13};

    constexpr uint8_t ONBOARD_LED = 2;
    constexpr uint8_t BUTTON = 3;
}

namespace Sensors {
    /**
     * @brief The I2C address of the ultrasonic sensor.
     */
    constexpr uint8_t US_ADDR = 0x77;
    /**
     * @brief The I2C address of the line following sensor.
     */
    constexpr uint8_t US_DIST_REG = 0x01;
    /**
     * @brief The address of the left LED's register.
     */
    constexpr uint8_t US_LEDL_REG = 0x02;
    /**
     * @brief The address of the right LED's register.
     */
    constexpr uint8_t US_LEDR_REG = 0x03;
    /**
     * @brief The maximum number of distances that can be stored in cache.
     */
    constexpr uint8_t US_CACHE_SIZE = 3;

    /**
     * @brief The I2C address of the line following sensor.
     */
    constexpr uint8_t LINE_ADDR = 0x78;
    /**
     * @brief The address of the line following sensor register.
     */
    constexpr uint8_t LINE_REG = 0x01;
}
