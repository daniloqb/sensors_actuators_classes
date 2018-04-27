/* 2018-04-25 -  Danilo Queiroz Barbosa
 * electronicdrops.com member
 * daniloqb@electronicdrops.com
 * 
 * This sketch is an example how to use the helper class TemperatureSensors.h, that tries
 * to build a same interface for diferent temperature sensor. 
 * Not worrying about the diferences and commands of its libraries.
 * For the moment is for simple use. To advanced use this helper class is not indicated.
 * 
 * Example for LM35 sensor connected on Analog Port A0. And with thresold Temperature Set.
 */


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
