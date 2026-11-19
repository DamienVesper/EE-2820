#pragma once

#include <Arduino.h>

class Drivetrain {
private:
    void motor(uint8_t idx, int16_t cmd);
public:
    void init();
    void stop();

    void fwd(uint8_t speed);
    void bwd(uint8_t speed);
    void setDir(int16_t left, int16_t right);
    void pivotCW(uint8_t speed);
    void pivotCCW(uint8_t speed);
};
