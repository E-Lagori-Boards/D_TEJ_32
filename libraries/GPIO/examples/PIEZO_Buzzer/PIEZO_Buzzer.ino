/*
  @file PIEZO_Buzzer.ino
  @brief Continuous beeping sound using Piezo Buzzer
  @detail Setting selected GPIO pin HIGH and LOW continuously (within small delay) to create beeping sound

   Reference aries board: https://vegaprocessors.in/blog/buzzer-with-aries-v2-board/
   
   *** Piezoelectric buzzer ***
   Connections:
   Buzzer     Aries Board
   VCC      -   3.3V
   GND      -   GND
   IN       -   GPIO0
*/

#define BUZZER 0 // connect INPUT pin of buzzer to GPIO-0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(BUZZER, HIGH); //turn on the buzzer
  delay(100);
  digitalWrite(BUZZER, LOW);  //turn off the buzzer
  delay(100);
}
