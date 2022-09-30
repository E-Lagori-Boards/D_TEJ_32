/*
  @file esp8266_post_demo.ino
  @brief ESP8266 Module communicates with the ARIES v2 Board via the UART Protocol
  @detail ESP8266 allows ARIES to connect to a Wi-Fi network and push data of any sensor to adafruit block

   Reference aries board: https://vegaprocessors.in/blog/esp8266-wifi-module-with-thejas-soc/
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
char * AP="CDAC"; // Add network name here
char * PASS= ""; // Add password
char * HOST="io.adafruit.com";
int PORT=80;
char * KEY="aio_hoUL61X7A3Ll7n7Gry5kwLA3MYOj";   // Replace Key here
char * URL="/api/v2/Himanshu_D/feeds/trial/data";  // Add URL of your feed here


int countTrueCommand;
int countTimeCommand; 
boolean found = false; 

int valSensor = 1;
char atcommand[250]={0,};
char data[250]={0,};
char payload[250]={0,};
int timeout=3;

int getSensorData(){
   return random(1000); // Replace with 
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

void loop() { 
  sendCommand("AT+CIPMUX=1",3,"OK");
  memset(atcommand,0,250);
  sprintf(atcommand,"AT+CIPSTART=0,\"TCP\",\"%s\",%d", HOST, PORT);
  sendCommand(atcommand,3,"OK");
  memset(atcommand,0,250);
   memset(data,0,250);
  sprintf(data,"{\"value\": %d}",getSensorData());
  sprintf(payload,"POST %s HTTP/1.1\r\nHost: %s\r\nContent-Type: application/json\r\nX-AIO-Key: %s\r\nContent-Length: %d\r\n\r\n%s",URL, HOST, KEY, strlen(data),data);
  sprintf(atcommand,"AT+CIPSEND=0,%d",strlen(payload));
  sendCommand(atcommand,4,">");
  esp8266.println(payload);
  countTrueCommand++;
  delay(20000);
  sendCommand("AT+CIPCLOSE=0",5,"OK");
}
