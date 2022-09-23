/*
* IR PROXIMITY SENSOR
* BLOG Link : https://vegaprocessors.in/blog/capturing-irinfrared-signals-using-aries/
*/


int IRSensor = 4; // connect OUT pin of IR sensor to aries GPIO-4
int LED = 22; // Green color LED is internally connected to GPIO-22

void setup() 
{
  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // Led pin OUTPUT
}

void loop()
{
  int statusSensor = digitalRead (IRSensor);
  
  if (statusSensor == 1){
    digitalWrite(LED, LOW); // LED LOW
  }
  
  else
  {
    digitalWrite(LED, HIGH); // LED High
  }
  
}