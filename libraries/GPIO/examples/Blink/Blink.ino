/**
  @file Blink.ino
  @brief contains routines for GPIO interface
  @detail Includes software functions declarations to initialize,configure, write and read LED over GPIO interface

   Reference arduino code: https://create.arduino.cc/projecthub/arohansenroy/blinking-led-56ffc9
   Refrence aries board: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf
   
   Connections:
   No external connections required to test this code. You can directly connect Aries board through USB and upload the program
   LED pins for Aries Board are: 
   pin no. 20,21 - Yellow LED (for Aries v2)
   Pin no. 22 - Green LED 
   Pin no. 23 - Blue LED
   Pin no. 24 - Red LED
   Note: BLUE,RED and GREEN LED will be in "ON" state for a digital "0" input and in "OFF" state for a digital "1" input.
         YELLOW LED will be in "ON" state for a digital "1" input and in "OFF" state for a digital "0" input.
 **/

int ledPin=22; // Green LED

void setup()
{
    pinMode(ledPin,OUTPUT);    //OUTPUT: Output mode
}
void loop()
{  
    digitalWrite(ledPin,HIGH); // LED OFF
    delay(1000);               // Set the delay time, 1000 = 1S
    digitalWrite(ledPin,LOW);  // LED ON
    delay(1000);               // Set the delay time, 1000 = 1S
} 
