#pragma once

#include <Arduino.h>

namespace Arena {
    constexpr float WIDTH = 8.0f;
    constexpr float HEIGHT = 8.0f;
    constexpr float TAPE_LENGTH = 1.50f;
    constexpr float CENTER_ZONE_REF = 1.00f;
    constexpr float HOME_ZONE_DEPTH = 0.75f;

    // TODO: Fix as needed.
    constexpr float CENTER_OFF_TAPE_EXT = 1.00f;
    constexpr float HOME_OFF_TAPE_EXT = 0.75f;
}

namespace Motion {
    constexpr float SPEED_CM_SEC = 15.0f;
    constexpr uint8_t TAPE_FOLLOW_SPEED = 32;
    constexpr uint8_t OFF_TAPE_SPEED = 25;
    constexpr uint8_t TURN_SPEED = 28;
    constexpr uint8_t ACQUIRE_SPEED = 25;
    constexpr uint8_t STEERING_CORRECTION = 18;
    /**
     * @brief Time spent turning 180 degrees, in milliseconds.
     */
    constexpr uint16_t TURN_180_MS = 1100;
    /**
     * @brief In milliseconds.
     */
    constexpr uint16_t LINE_ACQUIRE_TIMEOUT = 2500;
    /**
     * @brief In milliseconds.
     */
    constexpr uint16_t LINE_LOSS_DEBOUNCE = 250;
    /**
     * @brief In milliseconds.
     */
    constexpr uint16_t LINE_REACQUIRE_TIMEOUT = 1800;
    /**
     * @brief In milliseconds.
     */
    constexpr uint16_t PICKUP_SETTLE = 900;
    /**
     * @brief In milliseconds.
     */
    constexpr uint16_t DROP_SETTLE = 500;
    /**
     * @brief Mission timeout, in milliseconds.
     */
    constexpr uint16_t MISSION_TIMEOUT = 6e4;
    /**
     * @brief Stopping distance, in millimeters.
     */
    constexpr uint16_t STOP_DISTANCE = 250;
    /**
     * @brief Clearing distance, in millimeters.
     */
    constexpr uint16_t CLEAR_DISTANCE = 350;
    /**
     * @brief Time to clear, in milliseconds.
     */
    constexpr uint16_t CLEAR_STABLE = 500;
    /**
     * @brief Time to wait for object, in milliseconds.
     */
    constexpr uint16_t OBSTACLE_WAIT_TIMEOUT = 15e3;
}

namespace Pins {
    constexpr uint8_t MOTOR_PWM[4] = {10, 9, 6, 11};
    constexpr uint8_t MOTOR_DIR[4] = {12, 8, 7, 13};

    constexpr uint8_t ONBOARD_LED = 2;
    constexpr uint8_t BUTTON = 3;
    constexpr uint8_t ELECTROMAGNET = 5;
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
