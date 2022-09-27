/**
 @file RTC_SetTime.ino
 @brief contains routines for I2C Wire RTC interface
 @detail Includes software functions declarations to initialize,configure, write and read RTC over I2C interface

 * Reference for arduino code: DS1307 RTC library
 * Reference for aries board: https://vegaprocessors.in/blog/rtc-with-aries-v2-board/
 * DS1307 RTC 
 * Libraries used: TimeLib,DS1307RTC
 * Device address -0x77 & 0x68
 * Connections:
 * DS1307     Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * SDA      -   SDA0
 * SCL      -   SCL0
 * For connecting to port 1 (SCL1 and SDA1) of aries board use the default variable TwoWire Wire(1) instead of TwoWire Wire(0);
 * .
 **/

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

TwoWire Wire(0);

 bool parse=false;
 bool config=false;
  
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

void setup() {
  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

  Serial.begin(115200);
//  while (!Serial) ; // wait for Arduino Serial Monitor 
}

void loop() {
  delay(200);
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
  
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}
