#ifndef MOISTURE_H
#define MOISTURE_H

#include "driver/adc.h"

class MoistureSensor {
public:
    MoistureSensor();
    void init();
    int readMoistureLevel();

private:
    static const adc1_channel_t ADC_CHANNEL = ADC1_CHANNEL_0;
    static const int DRY_SOIL_VALUE = 4095;
    static const int WET_SOIL_VALUE = 1030;
    static const int NUM_READINGS = 10;

    int readings[NUM_READINGS];
    int readIndex;
    long total;
    int average;

    esp_adc_oneshot_handle_t adc_handle;

    int readADC();
};

#endif // MOISTURE_SENSOR_H
