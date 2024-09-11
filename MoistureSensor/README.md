# MoistureSensor Library

This library provides functionality for reading moisture levels from a sensor using the ESP32's ADC.

## Usage

```cpp
#include <MoistureSensor.h>

MoistureSensor sensor;

void setup() {
    sensor.init();
}

void loop() {
    int moistureLevel = sensor.readMoistureLevel();
    // Use the moistureLevel value
}
