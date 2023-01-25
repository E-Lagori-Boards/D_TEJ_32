/*
  @file MOTOR_DRIVER.ino
  @brief Interface L298N and L293D Motor Driver Module with Aries
  @detail To control the speed and spinning direction of a Small gear motor using the L298N & L293D Motor Driver
  
   Reference code: https://www.instructables.com/How-to-use-the-L293D-Motor-Driver-Arduino-Tutorial/ , 
                   https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/
   
   *** L298N Motor Driver ***
   Connections:
   L298N        Aries Board
   12V & 5V  -   5V
   GND       -   GND
   ENA       -   PWM 0
   ENB       -   PWM 1
   IN1       -   GPIO 11
   IN2       -   GPIO 12
   IN3       -   GPIO 13
   IN4       -   GPIO 15
    Note: L298N motor driver includes a 78M05 On-board 5V Regulator and Jumper that can be enabled or disabled via a jumper.
    If we are giving only 12V supply this regulator will internally produce 5V that is required for the driver module. 
    But here we are giving an external 5V power supply from our board, so remove the cap of 5V Regulator Enable Jumper while connecting.
    
    *** L293D Motor Driver ***
   Connections:
   L293D        Aries Board
   12V & 5V  -   5V
   GND       -   GND
   EN1       -   PWM 0
   EN2       -   PWM 1
   C1-A      -   GPIO 11
   C1-B      -   GPIO 12
   C2-A      -   GPIO 13
   C2-B      -   GPIO 15  
*/

//www.kuongshun.com

//    The direction specifications
//  ENA   ENB   IN1   IN2   IN3   IN4   Description  
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH   forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW    back
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH   left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW    right
//  HIGH  HIGH  LOW   LOW   LOW   LOW    stoped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH   stoped
//  LOW   LOW   N/A   N/A   N/A   N/A    stoped

#include<pwm.h>

//define Motor Driver module IO Pin
#define ENA 0   //Connect ENA to PWM0
#define ENB 1   //Connect ENB to PWM1
#define IN1 11    
#define IN2 12
#define IN3 13
#define IN4 15

void forward(){ 
  analogWrite(ENA,800000); //enable L298n A channel
  analogWrite(ENB,800000); //enable L298n B channel
  digitalWrite(IN1,HIGH); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 hight level
  Serial.println("Forward");//send message to serial monitor
}

void back(){
  analogWrite(ENA,800000);
  analogWrite(ENB,800000);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Back");
}

void left(){
  analogWrite(ENA,800000);
  analogWrite(ENB,800000);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  Serial.println("Left");
}

void right(){
  analogWrite(ENA,800000);
  analogWrite(ENB,800000);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  Serial.println("Right");
}

//before execute loop() function, 
//setup() function will execute first and only execute once
void setup() {

  Serial.begin(115200);//open serial and set the baudrate
  pinMode(IN1,OUTPUT);//before useing io pin, pin mode must be set first 
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  PWM.PWMC_Set_Period(ENA, 800000);
  PWM.PWMC_Set_Period(ENB, 800000);
}

//Repeat execution
void loop() {
  forward();  //go forward
  delay(1000);//delay 1000 ms
  back();     //go back
  delay(1000);
  left();     //turning left
  delay(1000);
  right();    //turning right
  delay(1000);
  
}
