#include "Bot.h"
#include "Arduino.h"
#include <Wire.h>

// i hate not having c++17 features.
const uint8_t MOTOR_PWM_PIN[4] = {10, 9, 6, 11};
const uint8_t MOTOR_DIR_PIN[4] = {12, 8, 7, 13};

void Bot::setup() {
    Serial.begin(9600);

    pinMode(START_KEY_PIN, INPUT);
    FastLED.addLeds<WS2812, START_LED_PIN, GRB>(leds, 1);
    this->setRGB(255, 0, 0);

    Wire.begin();
}

void Bot::setRGB(int idx, uint8_t r, uint8_t g, uint8_t b) {
    this->leds[idx].r = r;
    this->leds[idx].g = g;
    this->leds[idx].b = b;

    FastLED.show();
}

void Bot::setRGB(uint8_t r, uint8_t g, uint8_t b) {
    this->leds[0].r = r;
    this->leds[0].g = g;
    this->leds[0].b = b;

    FastLED.show();
}

void Bot::setMotors(const int8_t (&motors)[4]) {
    bool direction[4] = {1, 0, 0, 1};
    for (uint8_t i = 0; i < 4; i++) {
        digitalWrite(MOTOR_DIR_PIN[i], motors[i] < 0 ? !direction[i] : direction[i]);
        analogWrite(MOTOR_PWM_PIN[i], motors[i] == 0 ? 0 : map(abs(motors[i]), 0, 100, BOT_MOTOR_MIN_PWM, 255));
    }
}

void Bot::setVelocity(uint8_t speed, uint16_t angle, int8_t rotation, bool drift) {
    int8_t velocity[4] = {0, 0, 0, 0};

    float radAngle = angle * (PI / 180);
    float speedFactor = rotation == 0 ? 1 : 0.5;

    speed /= sqrt(2);

    if (drift) {
        velocity[0] = (speedFactor * (speed * sin(radAngle) - speed * cos(radAngle)));
        velocity[1] = (speedFactor * (speed * sin(radAngle) + speed * cos(radAngle)));
        velocity[2] = (speedFactor * (speed * sin(radAngle) - speed * cos(radAngle)) * (1 + rotation * 2));
        velocity[3] = (speedFactor * (speed * sin(radAngle) + speed * cos(radAngle)) * (1 + rotation * 2));
    } else {
        velocity[0] = (speedFactor * (speed * sin(radAngle) - speed * cos(radAngle)) * (1 + rotation));
        velocity[1] = (speedFactor * (speed * sin(radAngle) + speed * cos(radAngle)) * (1 + rotation));
        velocity[2] = (speedFactor * (speed * sin(radAngle) - speed * cos(radAngle)) * (1 + rotation));
        velocity[3] = (speedFactor * (speed * sin(radAngle) + speed * cos(radAngle)) * (1 + rotation));
    }

    this->setMotors(velocity);
}

void Bot::tick() {
    // Update sensor data.
    this->lineSensor.update();
    int distance = this->ultrasound.avgDistance();

    // this->setVelocity(50, 0, 0, false);

    switch (this->state) {
        case Tracking:
            if (this->lineSensor.ch2 == 1 && this->lineSensor.ch3 == 1) this->setVelocity(80, 0, 0, 0);
            if (this->lineSensor.ch2 == 1 && this->lineSensor.ch3 == 0) this->setVelocity(80, 0, 65, 0);
            if (this->lineSensor.ch2 == 0 && this->lineSensor.ch3 == 1) this->setVelocity(80, 0, -65, 0);

            while (this->lineSensor.ch2 == 0 && this->lineSensor.ch3 == 0) {
                this->lineSensor.update();
                this->ultrasound.setRGB(255, 255, 255);
                this->setVelocity(0, 0, 0, 0);
            }

            if (this->lineSensor.ch1 == 1 && this->lineSensor.ch4 == 1) this->state = Turning;
            else {
                if (distance < 50) this->ultrasound.setRGB(0, 0, 255);
                else this->ultrasound.setRGB(0, 255, 0);
            }
            break;
        case Turning:
            this->setVelocity(0, 0, 0, 0);
            delay(300);
            this->setVelocity(0, 0, -65, 0);
            delay(500);

            this->state = Tracking;
            break;
        case Picking:
            break;
        case Dropping:
            break;
    };
}

void Bot::loop() {
    keyState = analogRead(START_KEY_PIN);
    if (!keyState) active = 1;

    if (active) {
        this->setRGB(0, 255, 0);
        this->tick();
    }
}
