#pragma once

class LineSensor {
public:
    int ch1;
    int ch2;
    int ch3;
    int ch4;

    /**
     * @brief Update local sensor data.
     * 
     * @return `true` if successful, `false` otherwise.
     */
    bool update();
};
