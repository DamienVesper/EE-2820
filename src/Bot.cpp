#include "Bot.h"

void Bot::setup() {
    Serial.begin(9600);

    pinMode(START_KEY_PIN, INPUT);
    FastLED.addLeds<WS2812, START_LED_PIN>(leds, 1);
    this->setRGB(0, 255, 0, 0);

    claw.attach(SERVO_PIN);
    claw.write(170);
}

void Bot::setRGB(int idx, uint8_t r, uint8_t g, uint8_t b) {
    this->leds[idx].r = r;
    this->leds[idx].g = g;
    this->leds[idx].b = b;
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

    int distance = this->ultrasound.getDistance();

    if (distance >= 500) {
        claw.write(90);
    }
}

void Bot::loop() {
    if (!active) {
        active = analogRead(START_KEY_PIN);
        if (active) this->setRGB(0, 0, 255, 0);
    } else this->tick();
}
