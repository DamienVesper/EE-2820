#include "Bot.h"

Bot bot = Bot();

/**
 * @brief Called once at the beginning of program invocation. 
 */
void setup() {
    bot.setup();
}

/**
 * @brief Called repeatedly throughout the lifetime of the program.
 */
void loop() {
    bot.loop();
}
