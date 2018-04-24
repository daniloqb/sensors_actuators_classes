#include "TemperatureSensors.h"

TemperatureSensorLM35 sensor = TemperatureSensorLM35(A0,16);

void setup() {
  Serial.begin(9600);
  sensor.begin();

}

void loop() {
sensor.update();

float value = sensor.getTemperature();

Serial.println(value);

delay(1000);

}
