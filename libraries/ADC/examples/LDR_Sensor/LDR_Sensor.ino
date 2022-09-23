/*
* Interfacing Aries V2.0 with LDR sensor
* BLOG Link : https://vegaprocessors.in/blog/interfacing-ldr-sensor-to-aries-v2-board/
*/

#include <Wire.h>

TwoWire Wire(8);

#define LEDPIN  22 // Green LED is internally connected to GPIO-22 
#define LDRPIN  A0 // analog pin 0

void setup() { //  Void setup function will only run once, after each powerup or reset of the Arduino board.

Serial.begin(115200);

pinMode(LEDPIN, OUTPUT); // Here LED is determined as an ouput or an indicator.

pinMode(LDRPIN, INPUT); // Here LDR sensor is determined as input.

}

void loop() { // Void loop is ran again and again and contains main code.

int ldrStatus = analogRead(LDRPIN);

if (ldrStatus >= 1200) {

digitalWrite(LEDPIN, LOW); // If LDR senses darkness led pin high that means led will glow.

Serial.print("Darkness over here,turn on the LED : ");

Serial.println(ldrStatus);

} else {

digitalWrite(LEDPIN, HIGH); // If LDR senses light led pin low that means led will stop glowing.

Serial.print("There is sufficeint light , turn off the LED : ");

Serial.println(ldrStatus);

}

}