#include "Arduino.h"
#include "Config.h"
#include "Electromagnet.h"

void Electromagnet::init() {
    pinMode(Pins::ELECTROMAGNET, LOW);
};

void Electromagnet::start() {
    if (!state) {
        state = true;
        digitalWrite(Pins::ELECTROMAGNET, HIGH);
    }
}

void Electromagnet::stop() {
    if (state) {
        state = false;
        digitalWrite(Pins::ELECTROMAGNET, HIGH);
    }
}
