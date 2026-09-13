#ifndef BOT_H
#define BOT_H

#define BOT_LED_COUNT 1

#include <FastLED.h>
#include "LineFollower.h"
#include "Servo.h"
#include "Tractive.h"
#include "Ultrasound.h"

/**
 * @brief Singleton to condense access of all modules.
 */
class Bot {
private:
    // Sensors.
    LineFollower lineFollower;
    Ultrasound ultrasound;

    // Claw servo.
    Servo servo;

    // Motors.
    Tractive tractive;

    // FastLED colors.
    CRGB leds[BOT_LED_COUNT];

    // constant values
    static const uint8_t START_LED_PIN = 2;
    static const uint8_t START_KEY_PIN = 3;

    /**
     * @brief Whether the program is active or not.
     */
    int active = 0;

    /**
     * @brief Set the RGB of an LED via `FastLED`.
     * 
     * @param idx The index of the LED in the CRGB array.
     * @param r Red color (0 - 255).
     * @param g Green color (0 - 255).
     * @param b Blue color (0 - 255).
     */
    void setRGB(int idx, uint8_t r, uint8_t g, uint8_t b);
public:
    Bot();

    /**
     * @brief Loop logic when program is running. Kept outside of loop() for indentation reasons.
     */
    void setup();

    /**
     * @brief Called repeatedly throughout the lifetime of the program.
     */
    void loop();

    /**
     * @brief Loop logic when program is running.
     */
    void tick();
};

#endif
