/*
  @file DC_Relay_Demo.ino
  @brief Simple DC relay application
  @detail GREEN LED on the relay module will ON/OFF when the Relay is ON/OFF

   Reference aries board: https://vegaprocessors.in/blog/one-channel-relay-module-with-aries-v2-board/
   
   *** DC RELAY ***
   Connections:
   Relay     Aries Board
   VCC      -   3.3V
   GND      -   GND
   INP      -   GPIO0
*/


#define RELAY_PIN 0  // connect INPUT pin of DC Relay to GPIO-0 of Aries board 

char mode = 0xff;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  
  if(mode){
    Serial.println("Relay ON");
    digitalWrite(RELAY_PIN, HIGH);  //// let's turn ON the relay
  }else{
    Serial.println("Relay OFF");
    digitalWrite(RELAY_PIN, LOW);  //// turn OFF the relay
  }
  delayMicroseconds(400000);
  mode = ~(mode);
}
