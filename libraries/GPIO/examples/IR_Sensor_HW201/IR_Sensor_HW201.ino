/*
  @file IR_Sensor_HW201.ino
  @brief Capturing IR(Infrared) signals using ARIES
  @detail GREEN LED on the aries board will ON when the IR receiver receives infrared waves

   Reference aries board: https://vegaprocessors.in/blog/capturing-irinfrared-signals-using-aries/
   
   *** Infrared Proximity Sensor(HW-201) ***
   Connections:
   IR        Aries Board
   VCC      -   3.3V
   GND      -   GND
   OUT      -   GPIO4
*/

int IRSensor = 4; // connect OUTPUT pin of IR sensor to Aries GPIO-4
int LED = 22; // Green color LED is internally connected to GPIO-22

void setup() 
{
  pinMode (IRSensor, INPUT); // sensor pin INPUT
  pinMode (LED, OUTPUT); // Led pin OUTPUT
}

void loop()
{
  int statusSensor = digitalRead (IRSensor);   // reading sensor data
  
  if (statusSensor == 1){
    digitalWrite(LED, HIGH); // LED OFF 
  }
  
  else
  {
    digitalWrite(LED, LOW); // LED ON
  }
  
}
