#define PIN 2  // connect SIG pin of touch sensor to aries GPIO-0

void setup() {
  pinMode(PIN, INPUT);
  Serial.begin(115200);

}

void loop() {
  if (digitalRead(PIN) == HIGH)
    Serial.println("Sensor is touched");
  delay(500);
}