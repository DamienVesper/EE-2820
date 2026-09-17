#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

/**
 * @brief The I2C address of the line sensor.
 */
#define LINE_SENSOR_I2C_ADDR 0x78
/**
 * @brief The register address of the line sensor.
 */
#define LINE_SENSOR_REG 0x01

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

#endif
