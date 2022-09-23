/*
* DC RELAY MODULE
* BLOG Link : https://vegaprocessors.in/blog/one-channel-relay-module-with-aries-v2-board/
*/


#define RELAY_PIN 0  // connect INP pin of DC Relay to GPIO-0 of Aries board 

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