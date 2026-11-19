#include <Arduino.h>

#include "Config.h"
#include "Controller.h"

void Controller::start() {
    magnet.start();
    // startTime = millis();

    digitalWrite(Pins::ONBOARD_LED, LOW);
    setState(State::ACQUIRE_TAPE);
}

void Controller::stop() {
    drivetrain.stop();

    digitalWrite(Pins::ONBOARD_LED, HIGH);
    setState(State::FAULT);
}

void Controller::update() {
    uint32_t now = millis();

    // Update ultrasonic distance.
    if (now - lastSonarUpdate >= Sensors::US_INTERVAL) {
        lastSonarUpdate = now;
        sonar.getDistance();
    }

    if (buttonPressed()) {
        if (state == State::WAIT_START || state == State::COMPLETE) start();
        else if (state != State::FAULT) {
            drivetrain.stop();
            setState(State::WAIT_START);
        } 
    }

    if (state == State::WAIT_START || state == State::COMPLETE || state == State::FAULT) {
        drivetrain.stop();
        return;
    }

    // if (now - startTime > Motion::MISSION_TIMEOUT) {
    //     stop();
    //     return;
    // }

    const bool moveState = (
        state == State::ACQUIRE_TAPE
        || state == State::FOLLOW_TAPE_OUT
        || state == State::CENTER_APPROACH
        || state == State::RETURN_TO_TAPE
        || state == State::FOLLOW_TAPE_HOME
        || state == State::HOME_APPROACH
    );

    if (moveState && checkForObstacles()) {
        memoryState = state;
        drivetrain.stop();

        // pickupTime = now;
        // clearTime = 0;

        setState(State::OBSTACLE_PAUSE);
        return;
    }

    switch (state) {
        case State::ACQUIRE_TAPE:
            drivetrain.fwd(Motion::ACQUIRE_SPEED);
            if (now - lastSensorUpdate >= Sensors::UPDATE_INTERVAL) {
                lastSensorUpdate = now;
                line.update();

                if (line.ch2 && line.ch3) {
                    drivetrain.stop();
                    setState(State::FOLLOW_TAPE_OUT);
                }

                // if (now - )
            }
    }
}

void Controller::followLine() {
    // drivetrain.setDir(l, r);
}
