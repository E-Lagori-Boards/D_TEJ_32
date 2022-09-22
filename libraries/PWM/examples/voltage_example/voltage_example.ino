#include<Wire.h>
#define PIN A0  // Reading value from Analog pin 0
TwoWire Wire(8);

float Voltage; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Voltage = analogRead(PIN);
  Serial.print("Voltage = ");
  Serial.print(Voltage);
  Serial.println(" V");
  delay(2000);
}