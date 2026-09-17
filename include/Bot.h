#ifndef BOT_H
#define BOT_H

#include <FastLED.h>
#include "LineSensor.h"
#include <Servo.h>
#include "Ultrasound.h"

/**
 * @brief Number of LEDs (controllable by FastLED) on the bot.
 */
#define BOT_LED_COUNT 1
/**
 * @brief Minimum PWM to operate at.
 * PWM Pins (3, 5, 6, 9, 10, 11).
 * @link https://support.arduino.cc/hc/en-us/articles/9350537961500-Use-PWM-output-with-Arduino
 */
#define BOT_MOTOR_MIN_PWM 50

/**
 * @brief Current bot state to choose behavior.
 */
enum BotState {
    Tracking,
    Turning // At intersection.
};

/**
 * @brief Singleton to condense access of all modules.
 */
class Bot {
private:
    // Sensors.
    LineSensor lineSensor;
    Ultrasound ultrasound;

    // Claw servo.
    Servo claw;

    // FastLED colors.
    CRGB leds[BOT_LED_COUNT];

    /**
     * @brief Whether the program is active or not.
     */
    int active = 0;

    BotState state = Tracking;

    // Constant values.
    static const uint8_t START_LED_PIN = 2;
    static const uint8_t START_KEY_PIN = 3;

    static const uint8_t SERVO_PIN = 5;

    /**
     * @brief Set the RGB of an LED via `FastLED`.
     * 
     * @param idx The index of the LED in the CRGB array.
     * @param r Red color (0 - 255).
     * @param g Green color (0 - 255).
     * @param b Blue color (0 - 255).
     */
    void setRGB(int idx, uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Set PWM of all motors.
     * @param motors Constant reference to an array of power for motors.
     */
    void setMotors(const int8_t (&motors)[4]);

    /**
     * @brief Set the bot's velocity.
     * 
     * @param speed The speed to set.
     * @param angle The angle to apply the speed at.
     * @param rotation The rotation direction.
     * @param drift Whether you watch too much Fast & Furious or not.
     */
    void setVelocity(uint8_t speed, uint16_t angle, int8_t rotation, bool drift);
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
