/*
* VOLTAGE EXAMPLE
*/

#define PIN A0  // Reading value from Analog pin 0

float Voltage; 
float resolution = 0.002;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Voltage = resolution * (float)analogRead(PIN);
  Serial.print("Voltage = ");
  Serial.print(Voltage);
  Serial.println(" V");
  delay(1000);
}