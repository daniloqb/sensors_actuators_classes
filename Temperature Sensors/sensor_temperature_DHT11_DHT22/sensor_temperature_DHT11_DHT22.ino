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

TemperatureSensorDHT11 dht11 = TemperatureSensorDHT11(2);
TemperatureSensorDHT22 dht22 = TemperatureSensorDHT22(3);

void setup() {
  Serial.begin(9600);
  dht11.begin();
  dht22.begin();
}

void loop() {
dht11.update();
dht22.update();

Serial.println("DHT11");
Serial.print("Temperature: ");

Serial.print(dht11.getTemperature());
Serial.print("C ");

Serial.print(dht11.getTemperature('F'));
Serial.print("F ");

Serial.print(dht11.getTemperature('K'));
Serial.print("K ");
Serial.println();

Serial.print("Humidity: ");
Serial.print(dht11.getHumidity());
Serial.println("%");

Serial.println();

Serial.println("DHT22");
Serial.print("Temperature: ");

Serial.print(dht22.getTemperature());
Serial.print("C ");

Serial.print(dht22.getTemperature('F'));
Serial.print("F ");

Serial.print(dht22.getTemperature('K'));
Serial.print("K ");
Serial.println();

Serial.print("Humidity: ");
Serial.print(dht22.getHumidity());
Serial.println("%");

Serial.println();


delay(2000);

}
