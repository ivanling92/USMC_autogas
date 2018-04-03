// USMC Automated Gas Sensor System by Ivan Ling
// V1.0
// This version is the first version used for testing sensors only.

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal.h>
#include "MutichannelGasSensor.h"
#define ALTITUDE 24 // Altitude in USMC checked using https://elevationmap.net

Adafruit_BME280 bme; // I2C

String statusMessage;

void setup() {
    Serial.begin(9600);  // start serial for output

    //Grove Setup
    gas.begin(0x04);//the default I2C address of the slave is 0x04
    gas.powerOn();

    //BME Setup
    bme.begin(0x77);

}

void loop() {
  //Measures and print Grove Data
  printGas();
  printTHP();
  delay(500);
}

void printGas()
{
  float c;
  c = gas.measure_NO2();
  if(c>=0) Serial.print(c);
  else Serial.print("NA");
  Serial.print(",");
  
  c = gas.measure_CO();
  if(c>=0) Serial.print(c);
  else Serial.print("NA");
  Serial.print(",");
  
  c = gas.measure_NH3();
  if(c>=0) Serial.print(c);
  else Serial.print("NA");
  Serial.print(",");
  
  //c = gas.measure_CH4(); //Suspect invalid data
 // if(c>=0) Serial.print(c);
 // else Serial.print("NA");
 // Serial.print(",");
  
  c = gas.measure_H2();
  if(c>=0) Serial.print(c);
  else Serial.print("NA");
  Serial.print(",");
}

void printTHP()
{
  float temp;
  float humid;
  float pres;
  temp = bme.readTemperature();
  humid = bme.readHumidity();
  pres = bme.readPressure();
  pres = bme.seaLevelForAltitude(ALTITUDE,pres);
  pres = pres/100.0F;
  if(temp>=0) Serial.print(temp);
  else Serial.print("NA");
  Serial.print(",");
  if(humid>=0) Serial.print(humid);
  else Serial.print("NA");
  Serial.print(",");
  if(pres>=0) Serial.print(pres);
  else Serial.print("NA");
  Serial.println(" ");
  
}



