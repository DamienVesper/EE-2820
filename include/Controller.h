#pragma once

#include <Arduino.h>

#include "Electromagnet.h"
#include "Motors.h"
#include "LineSensor.h"
#include "Ultrasound.h"

class Controller {
public:
    void init();
    void update();
private:
    // TODO: Rename these to not give me an aneurysm when reading them.
    enum class State : uint8_t {
        WAIT_START,
        ACQUIRE_TAPE,
        FOLLOW_TAPE_OUT,
        CENTER_APPROACH,
        PICKUP_HOLD,
        TURN_TO_RETURN,
        RETURN_TO_TAPE,
        FOLLOW_TAPE_HOME,
        HOME_APPROACH,
        DROP,
        COMPLETE,
        OBSTACLE_PAUSE,
        FAULT
    };

    State state = State::WAIT_START;
    State memoryState = State::WAIT_START;

    Motors motors;
    LineSensor line;
    Ultrasound sonar;
    Electromagnet magnet;
};
