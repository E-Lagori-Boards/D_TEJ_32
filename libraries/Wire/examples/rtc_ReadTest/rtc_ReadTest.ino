/**
 @file rtc_ReadTest.ino
 @brief contains routines for I2C Wire RTC interface
 @detail Includes software functions declarations to initialize,configure, write and read RTC over I2C interface

 * Reference for arduino code: https://www.engineersgarage.com/Wire345-accelerometer-arduino-i2c/
 * Reference for aries board: https://vegaprocessors.in/blog/rtc-with-aries-v2-board/
 * ADXL345 accelerometer sensor
 * Device address -0x77 & 0x68
 * Connections:
 * ADXL345     Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * SDA      -   SDA1
 * SCL      -   SCL1
 * For connecting to port 0 (SCL0 and SDA0) of aries board use the default variable TwoWire Wire(0) instead of TwoWire Wire(1);
 * .
 **/


#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

TwoWire Wire(1);

void setup() {
  Serial.begin(115200);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
