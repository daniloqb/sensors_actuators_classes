#ifndef TemperatureSensors_h
#define TemperatureSensors_h

#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <max6675.h>
#include <SPI.h>


class TemperatureSensor{

  protected:
    float temperature;
    float tempAlarmHigh;
    float tempAlarmLow;
    void checkAlarm();

  public:
    boolean alarmHigh;
    boolean alarmLow;
    TemperatureSensor(){};
    float getTemperature(char scale);
    boolean setHighLimitAlarm(float temp);
    boolean setLowLimitAlarm(float temp);
    boolean getHighAlarm();
    boolean getLowAlarm();
    void update(){};
    void begin(){};
  
};

float TemperatureSensor::getTemperature( char scale='C'){

  switch (scale){
    case 'C':
        return temperature;
      break;
    case 'K':
        return (temperature + 273);
      break;
    case 'F':
        return ((temperature * 1.8) + 32);    
      break;
  }
}


boolean TemperatureSensor::setHighLimitAlarm(float temp){
  
//  if (temp < LM35_MIN_TEMPERATURE || temp > LM35_MAX_TEMPERATURE){
//    return false;
//  }

  tempAlarmHigh = temp;
  return true;
  
}

boolean TemperatureSensor::setLowLimitAlarm(float temp){
  
  //if (temp < LM35_MIN_TEMPERATURE || temp > LM35_MAX_TEMPERATURE){
  //  return false;
 // }

  tempAlarmLow = temp;
  return true;
  
}

boolean TemperatureSensor::getHighAlarm(){
  return alarmHigh;
}

boolean TemperatureSensor::getLowAlarm(){
  return alarmLow;
}

void TemperatureSensor::checkAlarm(){
    if (temperature >= tempAlarmHigh){
    alarmHigh = 1;
  } else {
    alarmHigh = 0;
  }
  if (temperature <= tempAlarmLow){
    alarmLow = 1;
  } else {
    alarmLow = 0;
  }
}





class TemperatureSensorLM35 : public TemperatureSensor{

  private:
    int sensor_pin;
    int resolution;
    float adc_reference;
    float voltage_reference;
   
    
  public:

void update();

    TemperatureSensorLM35(int pin_, int resolution_);
    TemperatureSensorLM35(int pin_, int resolution_, float adc_, float voltage_); 

    void setPin(int pin_);
    void setResolution(int resolution_);
    void setAdcReference(float adc_);
    void setVoltageReference(float voltage_);
  
};

TemperatureSensorLM35::TemperatureSensorLM35(int pin_, int resolution_=16){
  sensor_pin = pin_;
  resolution = resolution_;
  adc_reference = 1024.0;
  voltage_reference = 5.0;

  alarmHigh = 0;
  alarmLow = 0;
  tempAlarmHigh = 150;
  tempAlarmLow = -55;
}

TemperatureSensorLM35::TemperatureSensorLM35(int pin_, int resolution_, float adc_, float voltage_){

  sensor_pin = pin_;
  resolution = resolution_;
  adc_reference = adc_;
  voltage_reference = voltage_;

  alarmHigh = 0;
  alarmLow = 0;
  tempAlarmHigh = 150;
  tempAlarmLow = -55;
}

void TemperatureSensorLM35::update(){
  float values = 0;


  for (int i = 0; i < resolution; i++){
    values += analogRead(sensor_pin);
  }
  values /= resolution;
  float milivolts = ( values / adc_reference) * (voltage_reference * 1000);
  
  temperature = milivolts / 10;

  checkAlarm();
}

void TemperatureSensorLM35::setAdcReference(float adc_){
  adc_reference = adc_;
}

void TemperatureSensorLM35::setVoltageReference(float voltage_){
  voltage_reference = voltage_;
}


#define ONEWIRE_PIN_DEFAULT 2
#define DALLAS_DEFAULT_RESOLUTION 9

class TemperatureSensorDallas : public TemperatureSensor{
  private:
    int sensor_index;
    int onewire_pin;
    int resolution;
    OneWire * wo;
    DallasTemperature * sensors;

  public:
  TemperatureSensorDallas();
  TemperatureSensorDallas(int _onewire_pin);

    void begin();
    void update();


};


 TemperatureSensorDallas::TemperatureSensorDallas(){
  
  onewire_pin = ONEWIRE_PIN_DEFAULT;
  sensor_index = 0;
  resolution = DALLAS_DEFAULT_RESOLUTION;
 }

  TemperatureSensorDallas::TemperatureSensorDallas(int _onewire_pin){

  onewire_pin = _onewire_pin;
  sensor_index = 0;
  resolution = DALLAS_DEFAULT_RESOLUTION;
 }

void TemperatureSensorDallas::begin(){

  wo = new OneWire(onewire_pin);
  sensors = new DallasTemperature(wo);
  sensors->begin();
}

void TemperatureSensorDallas::update(){
  sensors->requestTemperatures();
  temperature = sensors->getTempCByIndex(sensor_index);

  checkAlarm();
}

class TemperatureSensorThermopar : public TemperatureSensor{

  private:
    MAX6675 thermocouple;

  public:
    TemperatureSensorThermopar();
    TemperatureSensorThermopar(int8_t SCLK, int8_t CS, int8_t MISO, double OFFSET = 0.0);
    TemperatureSensorThermopar(int8_t CS, double OFFSET = 0.0);
   
    begin(int8_t SCLK, int8_t CS, int8_t MISO, double OFFSET = 0.0);
    begin(int8_t CS, double OFFSET = 0.0);
    update();
    
};

TemperatureSensorThermopar::TemperatureSensorThermopar(){

  thermocouple = MAX6675();
}

TemperatureSensorThermopar::TemperatureSensorThermopar(int8_t SCLK, int8_t CS, int8_t MISO, double OFFSET = 0.0){

  thermocouple = MAX6675(SCLK, CS, MISO, OFFSET);
}

TemperatureSensorThermopar::TemperatureSensorThermopar(int8_t CS, double OFFSET = 0.0){

  thermocouple = MAX6675(CS, OFFSET);
}

TemperatureSensorThermopar::begin(int8_t SCLK, int8_t CS, int8_t MISO, double OFFSET){
  thermocouple.begin(SCLK, CS, MISO, OFFSET);
}

TemperatureSensorThermopar::begin(int8_t CS, double OFFSET){
  thermocouple.begin(CS,OFFSET);
}

TemperatureSensorThermopar::update(){
  temperature = thermocouple.readCelsius();
}


#endif
