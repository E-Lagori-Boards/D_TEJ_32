/*
  @file esp8266_get_demo.ino
  @brief ESP8266 Module communicates with the ARIES v2 Board via the UART Protocol
  @detail ESP8266 allows ARIES to connect to a Wi-Fi network and get data from adafruit to ON/OFF the RGB LED on Aries board

   Refrence aries board: https://vegaprocessors.in/blog/esp8266-wifi-module-with-thejas-soc/
   ESP8266 Pinout: https://raw.githubusercontent.com/AchimPieters/ESP8266-12F---Power-Mode/master/ESP8266_01X.jpg
   Adafruit IO : https://io.adafruit.com/
   
   *** ESP8266 WiFi Module ***
   Connections:
   ESP8266     Aries Board
   VCC      -   3.3V
   GND      -   GND
   RXD      -   TX1
   TXD      -   RX1
*/

#include <UARTClass.h>

UARTClass esp8266(1);
char * AP="Add Network name here";    
char * PASS= "Add Password here";
char * HOST="io.adafruit.com";
int PORT=80;
char * URL="/api/v2/Himanshu_D/feeds/trial/data/last?x-aio-key=aio_hoUL61X7A3Ll7n7Gry5kwLA3MYOj";  // Add URL of your feeds along with key

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
boolean ledon = false; 
int valSensor = 1;
char atcommand[250]={0,};
char data[250]={0,};

int getSensorData(){
  return 100; // Replace with 
}

void sendCommand(char * command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  { 
    esp8266.println(command);//at+cipsend
   
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("-> OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("-> Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
 
  found = false;
 }

 int checkButtonStatus()
 {
    int i=500;
    while(i){
       while(esp8266.available())
       {
          Serial.print(char(esp8266.read()));
       }
       i--;
    }
 }


void setup() {
  delay(2000);
  countTrueCommand=0;
  countTimeCommand=0;
  Serial.begin(115200);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  memset(atcommand,0,250);
  sprintf(atcommand,"AT+CWJAP=\"%s\",\"%s\"",AP,PASS);
  sendCommand(atcommand,2,"OK");
}
int timeout=3;
void loop() { 
  sendCommand("AT+CIPMUX=1",3,"OK");
  memset(atcommand,0,250);
  sprintf(atcommand,"AT+CIPSTART=0,\"TCP\",\"%s\",%d", HOST, PORT);
  sendCommand(atcommand,3,"OK");
  memset(atcommand,0,250);
  sprintf(data,"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", URL, HOST);
  sprintf(atcommand,"AT+CIPSEND=0,%d",strlen(data));
  sendCommand(atcommand,4,">");
  esp8266.println(data);
  countTrueCommand++;
  
  
  ledon=false;  
  timeout=5;
  while(timeout)
  { 
    if(esp8266.find("\"value\":\"1\""))
    {
        Serial.println("LED ON>>>>>>>>>");
        ledon=true;  
    }  
    timeout--;   
  }  
  
  if(ledon){
    digitalWrite(24,LOW);
    digitalWrite(22,LOW);
    digitalWrite(23,LOW);
  }
  else{
    digitalWrite(24,HIGH);
    digitalWrite(22,HIGH);
    digitalWrite(23,HIGH);
  }
  
  sendCommand("AT+CIPCLOSE=0",5,"OK");
 
}
