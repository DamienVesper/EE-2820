#include "Arduino.h"
#include "Config.h"
#include "Drivetrain.h"

void Drivetrain::motor(uint8_t i, int16_t cmd) {
    cmd = constrain(cmd, -100, 100);

    // Stolen from miniAuto tutorial. Hopefully it's correct.
    const bool polarity[4] = {true, false, false, true};
    if (!cmd) {
        analogWrite(Pins::MOTOR_PWM[i], 0);
        return;
    }

    digitalWrite(Pins::MOTOR_DIR[i], cmd > 0 ? polarity[i] : !polarity[i]);
    analogWrite(Pins::MOTOR_PWM[i], map(abs(cmd), 0, 100, 50, 255));
}

void Drivetrain::init() {
    for (uint8_t i = 0; i < 4; i++) {
        pinMode(Pins::MOTOR_PWM[i], OUTPUT);
        pinMode(Pins::MOTOR_DIR[i], OUTPUT);
        analogWrite(Pins::MOTOR_PWM[i], 0);
    }

    stop();
}

void Drivetrain::stop() {
    for (uint8_t i = 0; i < 4; i++) analogWrite(Pins::MOTOR_PWM[i], 0);
}

void Drivetrain::setDir(int16_t left, int16_t right) {
    const int16_t cmds[4] = {-left, right, -left, right};
    for (uint8_t i = 0; i < 4; i++) motor(i, cmds[i]);
}

void Drivetrain::fwd(uint8_t speed) {
    setDir(speed, speed);
}

void Drivetrain::bwd(uint8_t speed) {
    setDir(-(int16_t)speed, -(int16_t)speed);
}

void Drivetrain::pivotCW(uint8_t speed) {
    setDir(-(int16_t)speed, speed);
}

void Drivetrain::pivotCCW(uint8_t speed) {
    setDir(speed, -(int16_t)speed);
}
