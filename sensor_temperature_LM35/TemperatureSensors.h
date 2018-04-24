#ifndef TemperatureSensors_h
#define TemperatureSensors_h

#include "Arduino.h"


class TemperatureSensor{

  protected:
    float temperature;
    float threshold;
    boolean limit;

  public:
    TemperatureSensor(){};
    float getTemperature(char scale);
    void setThreshold(float temp);
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

void TemperatureSensor::setThreshold(float temp){
  threshold = temp;
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

TemperatureSensorLM35::TemperatureSensorLM35(int pin_, int resolution_){
  sensor_pin = pin_;
  resolution = resolution_;
  adc_reference = 1024.0;
  voltage_reference = 5.0;
}

TemperatureSensorLM35::TemperatureSensorLM35(int pin_, int resolution_, float adc_, float voltage_){

  sensor_pin = pin_;
  resolution = resolution_;
  adc_reference = adc_;
  voltage_reference = voltage_;
}

void TemperatureSensorLM35::update(){
  float values = 0;


  for (int i = 0; i < resolution; i++){
    values += analogRead(sensor_pin);
  }
  values /= resolution;
  float milivolts = ( values / adc_reference) * (voltage_reference * 1000);
  
  temperature = milivolts / 10;


}

void TemperatureSensorLM35::setAdcReference(float adc_){
  adc_reference = adc_;
}

void TemperatureSensorLM35::setVoltageReference(float voltage_){
  voltage_reference = voltage_;
}

#endif
