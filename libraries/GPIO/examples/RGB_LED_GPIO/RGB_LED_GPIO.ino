/*
  @file RGB_LED_GPIO.ino
  @brief Simple LED Application
  @detail Turning LEDs ON and OFF in simple serial pattern (in loop)
   
   *** RGB LED STRIP ***
   Connections:
   LED        Aries Board
   GND      -   GND
   R        -   GPIO0
   Y        -   GPIO1
   G        -   GPIO2
*/

#define RED_LED     0     // Connect Red LED pin to GPIO-0
#define YELLOW_LED  1     // Connect Yellow LED pin to GPIO-1
#define GREEN_LED   2     // Connect Green LED pin to GPIO-2

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RED_LED, HIGH);      // Red LED ON
  delay(1000);
  digitalWrite(YELLOW_LED, HIGH);   // Yellow LED ON
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);    // Green LED ON
  delay(1000);
  digitalWrite(GREEN_LED, LOW);     // Green LED OFF
  delay(1000);
  digitalWrite(YELLOW_LED, LOW);    // Yellow LED OFF
  delay(1000);
  digitalWrite(RED_LED, LOW);       // Red LED OFF
  delay(1000);
}
