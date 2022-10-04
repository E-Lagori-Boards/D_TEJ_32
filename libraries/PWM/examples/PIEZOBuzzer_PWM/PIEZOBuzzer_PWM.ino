/*
  @file PIEZOBuzzer_PWM.ino
  @brief Interfacing Piezo Buzzer with ARIES Board using PWM
  @detail varing duty cycle to turn volume of buzzer low-to-high and high-to-low repeatedly
  
   Reference aries board: https://vegaprocessors.in/blog/buzzer-with-aries-v2-board/
   
   *** Piezo Buzzer ***
   Connections:
   Buzzer     Aries Board
   VCC      -   3.3V
   GND      -   GND
   IN       -   PWM0
*/

#include <pwm.h>

#define BUZZER 0    // connect INPUT pin to PWM0 of Aries Board
int i;

void setup() {
  // put your setup code here, to run once:
  PWM.PWMC_Set_Period(BUZZER, 800000);  // setting period
}

void loop() {
  // put your main code here, to run repeatedly:
  for (i = 0; i < 400; i++)
  {
    analogWrite(BUZZER, i*2000);
    delay(10);
  }
  for (i = 400; i > 0; i--)
  {
    analogWrite(BUZZER, i*2000);
    delay(10);
  }
}
