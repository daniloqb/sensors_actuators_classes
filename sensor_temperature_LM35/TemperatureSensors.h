#ifndef TemperatureSensors_h
#define TemperatureSensors_h

#include "Arduino.h"


class TemperatureSensor{

  protected:
    float temperature;
    float thresholdUp;
    float thresholdDown;
    boolean limitUp;
    boolean limitDown;

    void checkThreshold();

  public:
    TemperatureSensor(){};
    float getTemperature(char scale);
    void setThreshold(float tempUp, float tempDown);
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

void TemperatureSensor::setThreshold(float tempUp, float tempDown = -55){
  thresholdUp = tempUp;
  thresholdDown = tempDown;
}


void TemperatureSensor::checkThreshold(){
  if (temperature > thresholdUp){
    limitUp = 1;
  } else {
    limitUp = 0;
  }
  if (temperature < thresholdDown){
    limitDown = 1;
  } else {
    limitDown = 0;
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

  limitUp = 0;
  limitDown = 0;
  thresholdUp = 150;
  thresholdDown = -55;
}

TemperatureSensorLM35::TemperatureSensorLM35(int pin_, int resolution_, float adc_, float voltage_){

  sensor_pin = pin_;
  resolution = resolution_;
  adc_reference = adc_;
  voltage_reference = voltage_;

  limitUp = 0;
  limitDown = 0;
  thresholdUp = 150;
  thresholdDown = -55;
}

void TemperatureSensorLM35::update(){
  float values = 0;


  for (int i = 0; i < resolution; i++){
    values += analogRead(sensor_pin);
  }
  values /= resolution;
  float milivolts = ( values / adc_reference) * (voltage_reference * 1000);
  
  temperature = milivolts / 10;

  checkThreshold();
}

void TemperatureSensorLM35::setAdcReference(float adc_){
  adc_reference = adc_;
}

void TemperatureSensorLM35::setVoltageReference(float voltage_){
  voltage_reference = voltage_;
}

#endif
