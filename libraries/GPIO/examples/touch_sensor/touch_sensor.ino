/*
  @file touch_sensor.ino
  @brief recording physical touch using touch sensor
  @detail "Sensor is touched" message will be display on serial monitor also green led will blink if sensor get touched
   Reference aries board: https://vegaprocessors.in/blog/ttp223b-touch-sensor-module-with-aries-v2-board/
   
   *** RGB LED STRIP ***
   Connections:
   Touch Sensor   Aries Board
   VCC          -   3.3V
   GND          -   GND
   SIG          -   GPIO0
*/

#define PIN 0  // connect SIGNAL pin to Aries GPIO-0

#define GREEN 22  // Green LED

void setup() {
  pinMode(PIN, INPUT);
  Serial.begin(115200);

}

void loop() {
  if (digitalRead(PIN) == HIGH){
    Serial.println("Sensor is touched");

    digitalWrite(GREEN, LOW);   // blink led if sensor is touched
    delay(50);
    digitalWrite(GREEN, HIGH);
  }
  delay(20);
}
