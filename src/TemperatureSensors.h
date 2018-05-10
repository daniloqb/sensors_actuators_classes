#ifndef TemperatureSensors_h
#define TemperatureSensors_h

#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <max6675.h>
#include <SPI.h>
#include <Thermistor.h>

class TemperatureSensor{

  protected:
    float m_temperature;
    float m_tempAlarmHigh;
    float m_tempAlarmLow;
    void checkAlarm();

  public:
    boolean m_alarmHigh;
    boolean m_alarmLow;
    TemperatureSensor(){};
    float getTemperature(char scale);
    boolean setHighLimitAlarm(float t_temp);
    boolean setLowLimitAlarm(float t_temp);
    boolean getHighAlarm();
    boolean getLowAlarm();
    void update(){};
    void begin(){};
  
};

float TemperatureSensor::getTemperature( char scale='C'){

  switch (scale){
    case 'C':
        return m_temperature;
      break;
    case 'K':
        return (m_temperature + 273);
      break;
    case 'F':
        return ((m_temperature * 1.8) + 32);    
      break;
  }
}


boolean TemperatureSensor::setHighLimitAlarm(float t_temp){
  
//  if (temp < LM35_MIN_TEMPERATURE || temp > LM35_MAX_TEMPERATURE){
//    return false;
//  }

  m_tempAlarmHigh = t_temp;
  return true;
  
}

boolean TemperatureSensor::setLowLimitAlarm(float t_temp){
  
  //if (temp < LM35_MIN_TEMPERATURE || temp > LM35_MAX_TEMPERATURE){
  //  return false;
 // }

  m_tempAlarmLow = t_temp;
  return true;
  
}

boolean TemperatureSensor::getHighAlarm(){
  return m_alarmHigh;
}

boolean TemperatureSensor::getLowAlarm(){
  return m_alarmLow;
}

void TemperatureSensor::checkAlarm(){
    if (m_temperature >= m_tempAlarmHigh){
    m_alarmHigh = 1;
  } else {
    m_alarmHigh = 0;
  }
  if (m_temperature <= m_tempAlarmLow){
    m_alarmLow = 1;
  } else {
    m_alarmLow = 0;
  }
}





class TemperatureSensorLM35 : public TemperatureSensor{

  private:
    int m_pin;
    int m_resolution;
    float m_adc;
    float m_voltage;
   
    
  public:

    void update();

    TemperatureSensorLM35(int t_pin, int t_resolution);
    TemperatureSensorLM35(int t_pin, int t_resolution, float t_adc, float t_voltage); 

    void setPin(int t_pin);
    void setResolution(int t_resolution);
    void setAdcReference(float t_adc);
    void setVoltageReference(float t_voltage);
  
};

TemperatureSensorLM35::TemperatureSensorLM35(int t_pin, int t_resolution=16){
  m_pin = t_pin;
  m_resolution = t_resolution;
  m_adc = 1024.0;
  m_voltage = 5.0;

  m_alarmHigh = 0;
  m_alarmLow = 0;
  m_tempAlarmHigh = 150;
  m_tempAlarmLow = -55;
}

TemperatureSensorLM35::TemperatureSensorLM35(int t_pin, int t_resolution, float t_adc, float t_voltage){

  m_pin = t_pin;
  m_resolution = t_resolution;
  m_adc = t_adc;
  m_voltage = t_voltage;

  m_alarmHigh = 0;
  m_alarmLow = 0;
  m_tempAlarmHigh = 150;
  m_tempAlarmLow = -55;
}

void TemperatureSensorLM35::update(){
  float values = 0;


  for (int i = 0; i < m_resolution; i++){
    values += analogRead(m_pin);
  }
  values /= m_resolution;
  float milivolts = ( values / m_adc) * (m_voltage * 1000);
  
  m_temperature = milivolts / 10;

  checkAlarm();
}

void TemperatureSensorLM35::setAdcReference(float t_adc){
  m_adc = t_adc;
}

void TemperatureSensorLM35::setVoltageReference(float t_voltage){
  m_voltage = t_voltage;
}


#define ONEWIRE_PIN_DEFAULT 2
#define DALLAS_DEFAULT_RESOLUTION 9

class TemperatureSensorDallas : public TemperatureSensor{
  private:
    int m_sensor_index;
    int m_onewire_pin;
    int m_resolution;
    OneWire * m_wo;
    DallasTemperature * m_sensors;

  public:
  TemperatureSensorDallas();
  TemperatureSensorDallas(int t_onewire_pin);

    void begin();
    void update();
};


 TemperatureSensorDallas::TemperatureSensorDallas(){
  
  m_onewire_pin = ONEWIRE_PIN_DEFAULT;
  m_sensor_index = 0;
  m_resolution = DALLAS_DEFAULT_RESOLUTION;
 }

  TemperatureSensorDallas::TemperatureSensorDallas(int t_onewire_pin){

  m_onewire_pin = t_onewire_pin;
  m_sensor_index = 0;
  m_resolution = DALLAS_DEFAULT_RESOLUTION;
 }

void TemperatureSensorDallas::begin(){

  m_wo = new OneWire(m_onewire_pin);
  m_sensors = new DallasTemperature(m_wo);
  m_sensors->begin();
}

void TemperatureSensorDallas::update(){
  m_sensors->requestTemperatures();
  m_temperature = m_sensors->getTempCByIndex(m_sensor_index);

  checkAlarm();
}

class TemperatureSensorThermopar : public TemperatureSensor{

  private:
    MAX6675 m_thermocouple;

  public:
    TemperatureSensorThermopar();
    TemperatureSensorThermopar(int8_t SCLK, int8_t CS, int8_t MISO, double OFFSET);
    TemperatureSensorThermopar(int8_t CS, double OFFSET);
   
    void begin(int8_t SCLK, int8_t CS, int8_t MISO, double OFFSET);
    void begin(int8_t CS, double OFFSET);
    void update();
    
};

TemperatureSensorThermopar::TemperatureSensorThermopar(){

  m_thermocouple = MAX6675();
}

TemperatureSensorThermopar::TemperatureSensorThermopar(int8_t SCLK, int8_t CS, int8_t MISO, double OFFSET = 0.0){

  m_thermocouple = MAX6675(SCLK, CS, MISO, OFFSET);
}

TemperatureSensorThermopar::TemperatureSensorThermopar(int8_t CS, double OFFSET = 0.0){

  m_thermocouple = MAX6675(CS, OFFSET);
}

void TemperatureSensorThermopar::begin(int8_t SCLK, int8_t CS, int8_t MISO, double OFFSET=0.0){
  m_thermocouple.begin(SCLK, CS, MISO, OFFSET);
}

void TemperatureSensorThermopar::begin(int8_t CS, double OFFSET=0.0){
 m_thermocouple.begin(CS,OFFSET);
}

void TemperatureSensorThermopar::update(){
  m_temperature = m_thermocouple.readCelsius();
}

class TemperatureSensorNTC : public TemperatureSensor{
  private:
    Thermistor * m_sensor;
 
  public:
  TemperatureSensorNTC();
  TemperatureSensorNTC(uint8_t t_pin_);
  TemperatureSensorNTC(uint8_t t_pin_, int t_ro, int t_rf);
  TemperatureSensorNTC(uint8_t t_pin_, int t_ro, int t_rf, int t_beta);

    void begin();
    void update();
};

TemperatureSensorNTC::TemperatureSensorNTC(){
  m_sensor = new Thermistor();
}

TemperatureSensorNTC::TemperatureSensorNTC(uint8_t t_pin_){
  m_sensor = new Thermistor(t_pin_);
}

TemperatureSensorNTC::TemperatureSensorNTC(uint8_t t_pin_, int t_ro, int t_rf){
  m_sensor = new Thermistor(t_pin_, t_ro, t_rf);
}

TemperatureSensorNTC::TemperatureSensorNTC(uint8_t t_pin_, int t_ro, int t_rf, int t_beta){
  m_sensor = new Thermistor(t_pin_, t_ro, t_rf, t_beta);
}

void TemperatureSensorNTC::begin(){}

void TemperatureSensorNTC::update(){
  
  m_temperature = m_sensor->getTemperature();
}


#endif
