/**
 @file ClockDisplay.ino
 @brief contains routines for TM1637 interface
 @detail Includes software functions declarations to initialize,configure, write and read TSM1637

 * Reference for arduino code: https://create.arduino.cc/projecthub/ryanchan/tm1637-digit-display-arduino-quick-tutorial-ca8a93
 * Reference for aries board: https://vegaprocessors.in/blog/tm1637-7-segment-display-with-aries-v2-0-board/
 * TM1637 seven segment display
 * 
 * Connections:
 * TM1637      Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * DI0      -   GPIO1
 * Clk      -   GPIO0
 * .
 **/

#include <TM1637.h>

int CLK = 1; //CLK of TM1637 is connected to GPIO1 pin of arduino
int DIO = 0;  //DI0 of TM1637 is connected to GPIO0 pin of arduino

TM1637 tm(CLK,DIO);

void setup() {
  // put your setup code here, to run once:
  tm.init();

  //set brightness; 0-7
  tm.set(2);
}

void loop() {
  // put your main code here, to run repeatedly:

  // example: "12:ab"
  // tm.display(position, character);
  tm.display(0,1);
  tm.display(1,2);
  tm.point(1);
  tm.display(2,10);
  tm.display(3,11);

  delay(1000);

  // example: "1234"
  displayNumber(1234);

  delay(1000);
}

void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}
