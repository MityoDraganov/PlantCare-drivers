#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H

class MoistureSensor {
public:
    // Constructor with pin parameter
    MoistureSensor(int pin);

    // Initialize the sensor
    void init();

    // Read the moisture level and return as a percentage
    int readMoistureLevel();

private:
    int _pin; // Analog pin where the sensor is connected

    // Calibration values based on measurements
    const int DRY_SOIL_VALUE = 4095; // Completely dry soil
    const int WET_SOIL_VALUE = 1030; // Most moist condition

    // Number of readings to average for smoothing
    const int NUM_READINGS = 10;

    // Array to hold sensor readings for averaging
    int readings[NUM_READINGS];
    int readIndex;
    long total;
    int average;
};

#endif // MOISTURE_SENSOR_H
