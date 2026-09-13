#include "Bot.h"
#include <Servo.h>
#include <FastLED.h>
#include <Wire.h>

Bot::Bot() {}

void Bot::setup() {
    Serial.begin(9600);

    pinMode(START_KEY_PIN, INPUT);
    FastLED.addLeds<WS2812, START_LED_PIN>(leds, 1);
    this->setRGB(0, 255, 0, 0);
}

void Bot::setRGB(int idx, uint8_t r, uint8_t g, uint8_t b) {
    this->leds[idx].r = r;
    this->leds[idx].g = g;
    this->leds[idx].b = b;
};

void Bot::tick() {
    // Update sensor data.
    this->lineSensor.update();
}

void Bot::loop() {
    if (!active) {
        active = analogRead(START_KEY_PIN);
        if (active) this->setRGB(0, 0, 255, 0);
    } else this->tick();
}
