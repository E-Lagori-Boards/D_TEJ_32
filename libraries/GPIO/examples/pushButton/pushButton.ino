/*
 @file   PushButton.ino
 @brief  contains routines for GPIO interface of push buttons
 @detail Red LED or Green LED will turn on if BTN-0 or BTN-1 is pressed respectivelly. 

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * Note: In this demo we are using built-in RGB LED
    * GPIO pin-22 - Green LED 
    * GPIO pin-23 - Blue LED
    * GPIO pin-24 - Red LED
    * RGB LED will be in "ON" state for a digital input "0" & in "OFF" state for a digital input "1".
    * GPIO pin-18 - BTN-1
    * GPIO pin-19 - BTN-0
    * ARIES v2 and IOT has two built-in Push Buttons.
*/

#define RED_LED       24
#define GREEN_LED     22
#define PUSH_BTN0     19
#define PUSH_BTN1     18

void setup() {
  // the setup function runs once when you press reset or power the board
  Serial.begin(115200);

  pinMode(PUSH_BTN0,INPUT); // Set the button-0 as an input
  pinMode(PUSH_BTN1,INPUT); // Set the button-1 as an input
}

void loop() {
  // the loop function runs over and over again forever
  if(digitalRead(PUSH_BTN0) == LOW) { // If button-0 is pressed
    digitalWrite(RED_LED, LOW); // turn the Red LED on
    Serial.println("BTN-0 is pressed");
  } else {
    digitalWrite(RED_LED, HIGH); // turn the LED off
  }

  if(digitalRead(PUSH_BTN1) == LOW) { // If button-1 is pressed
    digitalWrite(GREEN_LED, LOW); // turn the Green LED on
    Serial.println("BTN-1 is pressed");
  } else {
    digitalWrite(GREEN_LED, HIGH); // turn the LED off
  }
}
