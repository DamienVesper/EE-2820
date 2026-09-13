#include "Bot.h"
#include <Servo.h>
#include <FastLED.h>
#include <Wire.h>

Bot::Bot() {}

void Bot::setup () {
    Serial.begin(9600);

    pinMode(START_KEY_PIN, INPUT);
    FastLED.addLeds<WS2812, START_LED_PIN>(leds, 1);
    setRGB(0, 255, 255, 255);    
}

void Bot::setRGB (int idx, uint8_t r, uint8_t g, uint8_t b) {
    this->leds[idx].r = r;
    this->leds[idx].g = g;
    this->leds[idx].b = b;
};

void Bot::tick() {

}

void Bot::loop() {
    if (!active) active = analogRead(START_KEY_PIN);
    else this->tick();
}
