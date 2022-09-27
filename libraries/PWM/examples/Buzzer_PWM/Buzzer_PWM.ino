#include <pwm.h>

#define SPEAKER 0    // The speaker is on PWM-0
int i;


void setup() {
  // put your setup code here, to run once:
  PWM.PWMC_Set_Period(SPEAKER, 800000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (i = 0; i < 400; i++)
  {
    analogWrite(SPEAKER, i*2000);
    delay(10);
  }
  for (i = 400; i > 0; i--)
  {
    analogWrite(SPEAKER, i*2000);
    delay(10);
  }
}
