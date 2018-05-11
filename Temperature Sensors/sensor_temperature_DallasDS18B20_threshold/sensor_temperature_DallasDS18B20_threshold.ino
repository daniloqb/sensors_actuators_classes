/* 2018-04-27 -  Danilo Queiroz Barbosa
 * electronicdrops.com member
 * daniloqb@electronicdrops.com
 * 
 * This sketch is an example how to use the helper class TemperatureSensors.h, that tries
 * to build a same interface for diferent temperature sensor. 
 * Not worrying about the diferences and commands of its libraries.
 * For the moment is for simple use. To advanced use this helper class is not indicated.
 * 
 * Example for Dallas DS18B20 sensor connected on Digital Port 2. And with thresold Temperature Set.
 */


#include "TemperatureSensors.h"

TemperatureSensorDallas sensor = TemperatureSensorDallas();

void setup() {
  Serial.begin(9600);
  sensor.begin();

  sensor.setHighLimitAlarm(28.0);
  sensor.setLowLimitAlarm(26.0);
}

void loop() {
sensor.update();

Serial.print(sensor.getTemperature());
Serial.println('C');

Serial.println("Threshold: ");
Serial.print("Up: ");
Serial.print(sensor.getHighAlarm());
Serial.print(" Down: ");
Serial.println(sensor.getLowAlarm());
Serial.println();


delay(1000);

}
