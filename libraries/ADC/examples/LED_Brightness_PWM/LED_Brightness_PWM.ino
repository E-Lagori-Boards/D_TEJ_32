#include <pwm.h>

#define CH 1
int i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  PWM.PWMC_Set_Period(CH, 800000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(i = 0; i < 400; i++){
    analogWrite(CH, i);
    Serial.println(i);
    delay(10);
  }
  for(i = 400; i > 0; i--){
    analogWrite(CH, i);
    Serial.println(i);
    delay(10);
  }
}