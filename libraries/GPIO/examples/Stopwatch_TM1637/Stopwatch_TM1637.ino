/**
 @file Stopwatch.ino
 @brief contains routines for TM1637 interface
 @detail Includes software functions for working of TM1637 4 Digit 7-Segment Display with ARIES v2.0 Board

 * Reference arduino code:
 * Refrence aries board: https://vegaprocessors.in/blog/tm1637-7-segment-display-with-aries-v2-0-board/
 * TM1637 4 Digit 7-Segment Display 
 * Connections:
 * TM1637     Aries Board
 * VCC      -   3.3V
 * GND      -   GND
 * CLK      -   GPIO1
 * DIO      -   GPIO0
 * .
 **/

#include <EEPROM.h>
#include "Timer.h"
#include <avr/pgmspace.h>
#include "TM1637.h"
#define ON 1
#define OFF 0

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char microsecond_10 = 0;
unsigned char second;
unsigned char _microsecond_10 = 0;
unsigned char _second;
unsigned int eepromaddr;
boolean Flag_ReadTime;

#define CLK 1//pins definitions for TM1637 and can be changed to other ports
#define DIO 0
TM1637 tm1637(CLK,DIO);
Timer Timer(0);

void setup()
{
  Serial.begin(115200);
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.init();
  Timer.initialize(10000);//timing for 10ms
  Timer.stop();
  Timer.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
  Serial.println("Please send command to control the stopwatch:");
  Serial.println("S - start");
  Serial.println("P - pause");
  Serial.println("L - list the time");
  Serial.println("W - write the time to EEPROM ");
  Serial.println("R - reset");
}
void loop()
{
  char command;
  command = Serial.read();
  switch(command)
  {
    case 'S':stopwatchStart();Serial.println("Start timing...");break;
    case 'P':stopwatchPause();Serial.println("Stopwatch was paused");break;
    case 'L':readTime();break;
    case 'W':saveTime();Serial.println("Save the time");break;
    case 'R':stopwatchReset();Serial.println("Stopwatch was reset");break;
    default:break;
  }
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  }

}
//************************************************
void TimingISR()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second ++;
    if(second == 60)
    {
      second = 0;
    }
    microsecond_10 = 0;
  }
  ClockPoint = (~ClockPoint) & 0x01;
  if(Flag_ReadTime == 0)
  {
    _microsecond_10 = microsecond_10;
    _second = second;
  }
}
void TimeUpdate(void)
{
  if(ClockPoint)tm1637.point(POINT_ON);//POINT_ON = 1,POINT_OFF = 0;
  else tm1637.point(POINT_ON);
  TimeDisp[2] = _microsecond_10 / 10;
  TimeDisp[3] = _microsecond_10 % 10;
  TimeDisp[0] = _second / 10;
  TimeDisp[1] = _second % 10;
  Update = OFF;
}
void stopwatchStart()//timer1 on
{
  Serial.println("check 5");
  Flag_ReadTime = 0;
 Timer.start();

}
void stopwatchPause()//timer1 off if [CS12 CS11 CS10] is [0 0 0].
{
   Timer.stop();

}
void stopwatchReset()
{
   Serial.println("check 6");
  stopwatchPause();
  Flag_ReadTime = 0;
  _microsecond_10 = 0;
  _second = 0;
  microsecond_10 = 0;
  second = 0;
  Update = ON;
}
void saveTime()
{
  EEPROM.write(eepromaddr ++,microsecond_10);
  EEPROM.write(eepromaddr ++,second);
}
void readTime()
{
  Flag_ReadTime = 1;
  if(eepromaddr == 0)
  {
    Serial.println("The time had been read");
    _microsecond_10 = 0;
    _second = 0;
  }
  else{
  _second = EEPROM.read(-- eepromaddr);
  _microsecond_10 = EEPROM.read(-- eepromaddr);
  Serial.println("List the time");
  }
  Update = ON;
}
