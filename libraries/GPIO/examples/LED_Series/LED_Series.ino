/*
 @file   LED_Series.ino
 @brief  RGB LED
 @detail Various coloured LED will glow and color name will display on Serial Monitor
 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * Note: RGB LED will be in "ON" state for a digital input "0" & in "OFF" state for a digital input "1".
    * GPIO pin-22 - Green LED 
    * GPIO pin-23 - Blue LED
    * GPIO pin-24 - Red LED
*/

#define GREEN_LED     22
#define BLUE_LED      23
#define RED_LED       24

void setup() {
  // the setup function runs once when you press reset or power the board
  delay(1000);
  Serial.begin(115200);
}

void loop() {
  // the loop function runs over and over again forever
  digitalWrite(GREEN_LED, LOW);  // Green LED 
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  Serial.println("Green");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);  // Blue LED 
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  Serial.println("Blue");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);  // Red LED 
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  Serial.println("Red");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, LOW);  // Green + Blue = Cyan 
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  Serial.println("Cyan");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);  // Blue + Red = Purple
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  Serial.println("Purple");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, LOW);  // Green + RED = Lime
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  Serial.println("Lime");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, LOW);  // Green + Blue + Red = Light Blue
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  Serial.println("Light Blue");
  Serial.println("-----------");
  delay(1000);
}
