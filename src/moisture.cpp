#include "moisture.h"
#include <algorithm>
#include <iterator>

MoistureSensor::MoistureSensor() : readIndex(0), total(0), average(0) {
    std::fill(std::begin(readings), std::end(readings), 0);
}

void MoistureSensor::init() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_0);

    for (int i = 0; i < NUM_READINGS; i++) {
        readings[i] = readADC();
        total += readings[i];
    }
}

int MoistureSensor::readMoistureLevel() {
    total -= readings[readIndex];
    readings[readIndex] = readADC();
    total += readings[readIndex];
    readIndex = (readIndex + 1) % NUM_READINGS;
    average = total / NUM_READINGS;

    average = std::clamp(average, WET_SOIL_VALUE, DRY_SOIL_VALUE);

    int moisturePercentage = (average - WET_SOIL_VALUE) * 100 / (DRY_SOIL_VALUE - WET_SOIL_VALUE);
    return moisturePercentage;
}

int MoistureSensor::readADC() {
    return adc1_get_raw(ADC_CHANNEL);
}
