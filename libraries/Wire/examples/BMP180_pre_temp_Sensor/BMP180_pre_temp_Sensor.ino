/*
 @file bmp180_pre_temp_sensor.ino
 @brief contains routines for I2C Wire BMP180 sensor interface
 @detail Includes software functions declarations to initialize,configure, write and read BMP180 over I2C interface

 * Reference arduino code: https://lastminuteengineers.com/bmp180-arduino-tutorial/
 * Refrence aries board: https://vegaprocessors.in/blog/bmp180-digital-pressure-sensor-with-aries-v2-board/
 * Library Name : Adafruit BMP085 Library
 * 
 * BMP180 pressure temeperature sensor
 * Device address -0x77
 * Connections:
 * BMP180     Aries Board
 * VIN      -   3.3V
 * GND      -   GND
 * SDA      -   SDA1
 * SCL      -   SCL1
 * For connecting to port 0 (SCL 0 and SDA0) of aries board use the default variable TwoWire Wire(0) instead of TwoWire Wire(1);
*/



#include <Wire.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

Adafruit_BMP085 bmp;
  TwoWire Wire(1);
void setup() {
  Serial.begin(115200);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}
  
void loop() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
    Serial.println(" meters");
    
    Serial.println();
    delay(500);
}
