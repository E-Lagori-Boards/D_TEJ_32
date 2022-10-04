/*
  @file LDR_Sensor.ino
  @brief Interfacing LDR sensor with ARIES v2 
  @detail This demo read the LDR value and turns LED ON when LDR senses darkness.

   Refrence aries board: https://vegaprocessors.in/blog/interfacing-ldr-sensor-to-aries-v2-board/
   
   *** Optical Photosensitive LDR Sensor(LM393)  ***
   Connections:
   LDR       Aries Board
   VCC      -   3.3V
   GND      -   GND
   A0/OUT   -   A0
   D0       -   Not Required
*/

#define LEDPIN  22 // Green LED is internally connected to GPIO-22 
#define LDRPIN  A0 // analog pin 0

void setup() {

Serial.begin(115200);
pinMode(LEDPIN, OUTPUT); // Here LED is determined as an ouput or an indicator.
pinMode(LDRPIN, INPUT); // Here LDR sensor is determined as input.

}

void loop() { 
  
// Void loop is ran again and again and contains main code.
int ldrStatus = analogRead(LDRPIN);  // resitance value // higher the light intensity, lower the resistance

if (ldrStatus >= 1200) {
  digitalWrite(LEDPIN, LOW); // If LDR senses darkness led pin high that means led will glow.
  Serial.print("Darkness over here,turn on the LED : ");
  Serial.println(ldrStatus);
} else {
  digitalWrite(LEDPIN, HIGH); // If LDR senses light led pin low that means led will stop glowing.
  Serial.print("There is sufficeint light , turn off the LED : ");
  Serial.println(ldrStatus);
  }
}
