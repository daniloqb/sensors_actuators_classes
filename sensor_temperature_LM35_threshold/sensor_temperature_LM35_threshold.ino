#include "TemperatureSensors.h"

TemperatureSensorLM35 sensor = TemperatureSensorLM35(A0);

void setup() {
  Serial.begin(9600);
  sensor.begin();

  sensor.setThreshold(27.0,25.5);
}

void loop() {
sensor.update();

Serial.print(sensor.getTemperature());
Serial.println('C');

Serial.println("Threshold: ");
Serial.print("Up: ");
Serial.print(sensor.limitUp);
Serial.print(" Down: ");
Serial.println(sensor.limitDown);
Serial.println();


delay(1000);

}
