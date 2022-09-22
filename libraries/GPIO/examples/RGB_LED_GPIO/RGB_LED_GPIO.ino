/*
 * RGB LED STRIP
 */

#define RED_LED 0  // Connect RED LED pin to GPIO-0
#define YELLOW_LED 1  // Connect YELLOW LED pin to GPIO-1
#define GREEN_LED 2 // Connect GREEN LED pin to GPIO-2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RED_LED, HIGH);
  delay(1000);
  digitalWrite(YELLOW_LED, HIGH);
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);
  delay(1000);
  digitalWrite(GREEN_LED, LOW);
  delay(1000);
  digitalWrite(YELLOW_LED, LOW);
  delay(1000);
  digitalWrite(RED_LED, LOW);
  delay(1000);
}