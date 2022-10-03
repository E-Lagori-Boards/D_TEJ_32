/*
  @file RGB_LED_PWM.ino
  @brief LED Breathing
  @detail LED Brightness using PWM
   
   *** RGB LED Strip ***
   Connections:
   LED STRIP     Aries Board
   GND        -   GND
   R          -   PWM0
   Y          -   PWM1
   G          -   PWM2
*/

#include <pwm.h>

#define RED_LED 0  // Red LED to PWM0
#define YELLOW_LED 1  // Yellow LED to PWM1
#define GREEN_LED 2 // Green LED to PWM2

int i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  PWM.PWMC_Set_Period(RED_LED, 800000);  // Setting period to 800000
  PWM.PWMC_Set_Period(YELLOW_LED, 800000);
  PWM.PWMC_Set_Period(GREEN_LED, 800000);
}

void loop() {
  // put your main code here, to run repeatedly:
   for(i = 0; i < 400; i++){
    analogWrite(RED_LED, i*2000);
    analogWrite(YELLOW_LED, i*2000);
    analogWrite(GREEN_LED, i*2000);
    delay(10);
  }
  for(i = 400; i > 0; i--){
    analogWrite(RED_LED, i*2000);
    analogWrite(YELLOW_LED, i*2000);
    analogWrite(GREEN_LED, i*2000);
    delay(10);
  }
}
