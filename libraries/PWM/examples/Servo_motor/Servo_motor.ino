#include <Servo.h>
#define CH 1 // connect signal PIN to PWM-0 of Aries Board
Servo myservo;  // create servo object to control a servo

int i;

void setup() {
  myservo.attach(CH);  // attaches the servo on PWM-0
}

void loop() {
for(i=0 ; i<=180; i++){
  myservo.write(i);                  // sets the servo position according to the scaled value
}

for(i=180 ; i>=0; i--){
  myservo.write(i);                  // sets the servo position according to the scaled value
}
}