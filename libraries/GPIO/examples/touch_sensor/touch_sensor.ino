#define PIN 2  // connect SIG pin of touch sensor to aries GPIO-2

#define GREEN 22

void setup() {
  pinMode(PIN, INPUT);
  Serial.begin(115200);

}

void loop() {
  if (digitalRead(PIN) == HIGH){
    Serial.println("Sensor is touched");

    digitalWrite(GREEN, LOW);
    delay(50);
    digitalWrite(GREEN, HIGH);
  }
  delay(20);
}