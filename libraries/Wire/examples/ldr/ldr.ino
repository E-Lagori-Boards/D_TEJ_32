/**
 @file ldr.ino
 @brief contains routines for I2C Wire LDR interface
 @detail Includes software functions declarations to initialize,configure, write and read LDR over I2C interface

 * Reference arduino code: https://create.arduino.cc/projecthub/electronicsfan123/interfacing-arduino-uno-with-ldr-8760ba
 * Refrence aries board: https://vegaprocessors.in/blog/interfacing-ldr-sensor-to-aries-v2-board/
 * LDR Light Dependent Resistor
 * Connections:
 * ADXL345     Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * SDA      -   SDA1
 * SCL      -   SCL1
 * For connecting to port 0 (SCL 0 and SDA0) of aries board, use the default variable TwoWire Wire(0) instead of TwoWire Wire(1);
 * .
 **/

#include <Wire.h>
const int ledPin = 21; // digital pin 5 
const int ldrPin = A0; // analog pin 0

TwoWire Wire(1);
void setup() { //  Void setup function will only run once, after each powerup or reset of the Arduino board.

Serial.begin(115200);

pinMode(ledPin, OUTPUT); // Here LED is determined as an ouput or an indicator.

pinMode(ldrPin, INPUT); // Here LDR sensor is determined as input.

}

void loop() { // Void loop is ran again and again and contains main code.

int ldrStatus = analogRead(ldrPin);

if (ldrStatus <= 200) {

digitalWrite(ledPin, HIGH); // If LDR senses darkness led pin high that means led will glow.

Serial.print("Darkness over here,turn on the LED : ");

Serial.println(ldrStatus);

} else {

digitalWrite(ledPin, LOW); // If LDR senses light led pin low that means led will stop glowing.

Serial.print("There is sufficeint light , turn off the LED : ");

Serial.println(ldrStatus);

}

}
