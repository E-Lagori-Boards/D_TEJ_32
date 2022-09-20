/**
  @file Blink.ino
  @brief contains routines for GPIO interface
  @detail Includes software functions declarations to initialize,configure, write and read LED over GPIO interface

   Reference arduino code: https://create.arduino.cc/projecthub/arohansenroy/blinking-led-56ffc9
   Refrence aries board: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf
   
   Connections:
   No external connections required to test this code. You can directly connect Aries board through USB and upload the program
   LED pins for Aries Board are: 
   pin no. 20,21 - Yellow LED
   Pin no. 22 - Green LED 
   Pin no. 23 - Blue LED
   Note: BLUE and GREEN LED will be in "ON" state for a digital "0" input and in "OFF" state for a digital "1" input.
         YELLOW LED will be in "ON" state for a digital "1" input and in "OFF" state for a digital "0" input.
 **/

int ledPin=22; //definition digital 8 pins as pin to control the LED
void setup()
{
    pinMode(ledPin,OUTPUT);    //Set the digital 8 port mode, OUTPUT: Output mode
}
void loop()
{  
    digitalWrite(ledPin,HIGH); //HIGH is set to about 5V PIN8
    delay(1000);               //Set the delay time, 1000 = 1S
    digitalWrite(ledPin,LOW);  //LOW is set to about 5V PIN8
    delay(1000);               //Set the delay time, 1000 = 1S
} 
