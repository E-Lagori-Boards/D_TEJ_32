/*
* BEEP SOUND USING PIEZO BUZZER
* Blog Link : https://vegaprocessors.in/blog/buzzer-with-aries-v2-board/
*/

#define BUZZER 0 // connect IN pin of buzzer to GPIO-0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BUZZER, HIGH); //turn on the buzzer
  delay(100);
  digitalWrite(BUZZER, LOW);  //turn off the buzzer
  delay(100);
}