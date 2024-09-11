#include "MoistureSensor.h"
#include <Arduino.h>

MoistureSensor::MoistureSensor(int pin) : _pin(pin), readIndex(0), total(0), average(0) {
    // Initialize all readings to the initial sensor value
    for (int i = 0; i < NUM_READINGS; i++) {
        readings[i] = analogRead(_pin);
        total += readings[i];
    }
}

void MoistureSensor::init() {
    pinMode(_pin, INPUT);
}

int MoistureSensor::readMoistureLevel() {
    // Subtract the last reading
    total -= readings[readIndex];
    
    // Read the sensor
    readings[readIndex] = analogRead(_pin);
    
    // Add the new reading to the total
    total += readings[readIndex];
    
    // Advance to the next position in the array
    readIndex = (readIndex + 1) % NUM_READINGS;
    
    // Calculate the average of the readings
    average = total / NUM_READINGS;

    // Clamp the average value to within the expected range
    if (average > DRY_SOIL_VALUE) {
        average = DRY_SOIL_VALUE;
    } else if (average < WET_SOIL_VALUE) {
        average = WET_SOIL_VALUE;
    }

    // Normalize the average sensor value to a percentage (0% dry, 100% wet)
    int moisturePercentage = map(average, DRY_SOIL_VALUE, WET_SOIL_VALUE, 0, 100);

    return moisturePercentage;
}
