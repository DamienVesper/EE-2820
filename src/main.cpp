#include "Controller.h"

Controller controller;

/**
 * @brief Called once at the beginning of program invocation. 
 */
void setup() {
    controller.init();
}

/**
 * @brief Called repeatedly throughout the lifetime of the program.
 */
void loop() {
    controller.update();
}
