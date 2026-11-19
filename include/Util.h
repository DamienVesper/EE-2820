#pragma once

#include <Arduino.h>

class Util {
public:
    /**
     * @brief Get a duration, in milliseconds.
     * @param dist The distance, in feet.
     * @param speed The speed, in cm/s.
     */
    static uint32_t duration(float dist, float speed);
};
