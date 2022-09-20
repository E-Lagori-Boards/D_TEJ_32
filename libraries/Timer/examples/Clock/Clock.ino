/**
 @file TSM1637_accelerometer.ino
 @brief contains routines for I2C TSM1637 interface
 @detail Includes software functions declarations to initialize,configure, write and read TSM1637 over I2C interface

 * Reference: https://create.arduino.cc/projecthub/ryanchan/tm1637-digit-display-arduino-quick-tutorial-ca8a93
 * TSM1637 seven segment display
 * 
 * Connections:
 * TSM1637     Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * DI0      -   GPIO1
 * Clk      -   GPIO0
 * .
 **/

#include <TM1637.h>

int CLK = 1;
int DIO = 0;

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
