/* 2018-04-25 -  Danilo Queiroz Barbosa
 * electronicdrops.com member
 * daniloqb@electronicdrops.com
 * 
 * This sketch is an example how to use the helper class TemperatureSensors.h, that tries
 * to build a same interface for diferent temperature sensor. 
 * Not worrying about the diferences and commands of its libraries.
 * For the moment is for simple use. To advanced use this helper class is not indicated.
 * 
 * Example for LM35 sensor connected on Analog Port A0.
 */



#include "TemperatureSensors.h"

TemperatureSensorAM2320 sensor = TemperatureSensorAM2320();

void setup() {
  Serial.begin(9600);
  sensor.begin();
}

void loop() {
sensor.update();
Serial.print("Temperature: ");

Serial.print(sensor.getTemperature());
Serial.print("C ");

Serial.print(sensor.getTemperature('F'));
Serial.print("F ");

Serial.print(sensor.getTemperature('K'));
Serial.print("K ");
Serial.println();

Serial.print("Humidity: ");
Serial.print(sensor.getHumidity());
Serial.println("%");

Serial.println();


delay(2000);

}
