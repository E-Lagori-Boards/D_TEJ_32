/*
* PIR MOTION SENSOR
* BLOG Link : https://vegaprocessors.in/blog/pir-motion-sensor-with-vega-processors/
*/


int led = 22;                // the pin that the LED is atteched to GPIO-22 internally
int sensor = 0;              // the pin that the sensor is atteched to GPIO-0 of Aries Board
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)


// VCC - 5V

void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(115200);        // initialize serial
}

void loop(){
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}
