#pragma once

#include <Arduino.h>

#include "Drivetrain.h"
#include "Electromagnet.h"
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

    Drivetrain drivetrain;
    LineSensor line;
    Ultrasound sonar;
    Electromagnet magnet;

    // Timers! I love timers (I hate timers in C++ but I love timers everywhere else!).
    uint32_t
        lastSensorUpdate = 0,
        lastSonarUpdate = 0;

    bool buttonLastState = HIGH;
    bool buttonCurrentState = HIGH;

    void start();
    void stop();
    void followLine();
    void setState (State state);

    bool buttonPressed();
    bool checkForObstacles() const;
};
