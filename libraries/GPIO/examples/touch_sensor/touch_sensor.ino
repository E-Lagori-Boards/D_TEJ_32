/*
* TOUCH SENSOR
* BLOG Link : https://vegaprocessors.in/blog/ttp223b-touch-sensor-module-with-aries-v2-board/
*/


#define PIN 0  // connect SIG pin of touch sensor to aries GPIO-0

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