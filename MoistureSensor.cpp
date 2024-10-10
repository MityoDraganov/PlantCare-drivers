#include "MoistureSensor.h"
#include <algorithm>
#include <Arduino.h>

// Static instance of the MoistureSensor
static MoistureSensor moistureSensor;

MoistureSensor::MoistureSensor() : readIndex(0), total(0), average(0) {
    Serial.println("MoistureSensor constructor called");
    SensorManager::registerSensor(this);
    std::fill(std::begin(readings), std::end(readings), 0);
}

void MoistureSensor::init() {
    Serial.println("Initializing Moisture Sensor...");
    // ADC Configuration: Set width and attenuation
    adc1_config_width(ADC_WIDTH_BIT_12);  // Set to 12-bit resolution (0-4095)
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);  // Set attenuation for full-scale voltage (0-3.3V)
}

int MoistureSensor::readValue() {
    // Average multiple readings to smooth the value
    total = 0;
    for (int i = 0; i < NUM_READINGS; i++) {
        readings[i] = readADC();
        total += readings[i];
    }
    average = total / NUM_READINGS;

    // Convert the averaged sensor reading to a percentage
    int percentage = (DRY_SOIL_VALUE - average) * 100 / (DRY_SOIL_VALUE - WET_SOIL_VALUE);

    // Clamp the percentage to be within 0 - 100 range
    percentage = std::max(0, std::min(100, percentage));

    return percentage;  // Return the moisture level as a percentage
}

int MoistureSensor::readADC() {
    // Read the ADC value from the moisture sensor (VP pin, GPIO36)
    return adc1_get_raw(ADC_CHANNEL);  // Read the raw ADC value from channel 0 (GPIO36)
}

const char* MoistureSensor::getType() {
    return "MoistureSensor";  // Return the sensor type as a string
}
