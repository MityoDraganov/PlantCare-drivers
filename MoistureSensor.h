#ifndef MOISTURESENSOR_H
#define MOISTURESENSOR_H

#include "../Sensor/Sensor.h"
#include "../SensorManager/SensorManager.h"
#include <algorithm>
#include <iterator>
#include "driver/adc.h"

class MoistureSensor : public Sensor {
public:
    MoistureSensor();  // Constructor declaration

    void init() override;  // Initialize the moisture sensor (ADC setup)
    int readValue() override;  // Read and return the averaged moisture sensor value
    const char* getType() override;  // Return the type of the sensor

private:
    // GPIO36 (VP) corresponds to ADC1_CHANNEL_0
    static const adc1_channel_t ADC_CHANNEL = ADC1_CHANNEL_0;

    // Calibration values (optional, based on your sensor)
    static const int DRY_SOIL_VALUE = 4095;
    static const int WET_SOIL_VALUE = 1030;

    // Number of readings for smoothing
    static const int NUM_READINGS = 10;

    int readings[NUM_READINGS];  // Array to store multiple readings for averaging
    int readIndex;  // Current index for reading
    long total;  // Sum of all readings
    int average;  // Averaged reading

    int readADC();  // Function to read the raw ADC value
};

#endif // MOISTURESENSOR_H
