#include "TemperatureSensors.h"

TemperatureSensorLM35 sensor = TemperatureSensorLM35(A0);

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
sensor.update();
Serial.println("Reading Temperature");
Serial.println();

Serial.print(sensor.getTemperature());
Serial.println('C');

Serial.print(sensor.getTemperature('F'));
Serial.println('F');

Serial.print(sensor.getTemperature('K'));
Serial.println('K');

Serial.println();


delay(1000);

}
