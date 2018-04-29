/* 2018-04-29 -  Danilo Queiroz Barbosa
 * electronicdrops.com member
 * daniloqb@electronicdrops.com
 * 
 * This sketch is an example how to use the helper class TemperatureSensors.h, that tries
 * to build a same interface for diferent temperature sensor. 
 * Not worrying about the diferences and commands of its libraries.
 * For the moment is for simple use. To advanced use this helper class is not indicated.
 * 
 * Example for Thermopar with MAX6675 sensor connected on SPI Software.
 */

#include "TemperatureSensors.h"


// pins where sensor is connected
int sensor_DO = 6;
int sensor_CS = 5;
int sensor_CLK = 4;

// using digital ports as sensor power source
int vccPin = 3;
int gndPin = 2;


TemperatureSensorThermopar sensor = TemperatureSensorThermopar();

void setup() {

    // use Arduino pins
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  
  Serial.begin(9600);
  sensor.begin(sensor_CLK,sensor_CS,sensor_DO);

  
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
