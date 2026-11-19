#pragma once

#include <Arduino.h>


class Electromagnet {
private:
    bool state = false;
public:
    void init();
    void start();
    void stop();
};
