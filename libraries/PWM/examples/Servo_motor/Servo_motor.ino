/*
  @file Servo_motor.ino
  @brief Interfacing servo motor with Aries V2
  @detail Rotating servo motor 

   Reference aries board: https://vegaprocessors.in/blog/servo-motors-with-aries-v2-board/
   
   *** Servo Motor(SG90) ***
   Connections:
   Servo Motor     Aries Board
   VCC          -   3.3V
   GND          -   GND
   SIG          -   PWM0
*/

#include <Servo.h>

#define CH 0 // connect signal PIN to PWM-0 of Aries Board
Servo myservo;  // create servo object to control a servo

int i;

void setup() {
  myservo.attach(CH);  // attaches the servo on PWM-0
}

void loop() {
for(i=0 ; i<=180; i++){
  myservo.write(i);                  // sets the servo position according to the scaled value
}

for(i=180 ; i>=0; i--){
  myservo.write(i);                  // sets the servo position according to the scaled value
}
}
