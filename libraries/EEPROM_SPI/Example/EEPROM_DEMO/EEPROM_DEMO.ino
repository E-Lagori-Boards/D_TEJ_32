#include<SPI.h>
#include<at25sf161.h>

int ret;

void setup() {
  // put your setup code here, to run once:
  static unsigned char *arr;
                      
  SPIClass SPI(3);              // initialize the SPI port-3 

  arr = EEPROM.at25sf161Begin();                                
  Serial.print("[INFO] eeprom ");
  Serial.print(arr[0], HEX);
  Serial.print(":");
  Serial.print(arr[1], HEX);
  Serial.print(":");
  Serial.print(arr[2], HEX);
  Serial.print(" initialized at");
  Serial.println(" spi3.");
  //SPI.beginTransaction(SPISettings(25000000, MSBFIRST, SPI_MODE3));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned char writeData[256], readData[512];

  Serial.println();
  Serial.println("+------[ AT25SF161  Demo ]------+");
  Serial.println("|                               |");
  Serial.println("|     AT25SF161  ----> SPI3     |");
  Serial.println("|                               |");
  Serial.println("+-------------------------------+");
  Serial.println();

  Serial.println("[WARN] executing full chip erase at spi3");
  ret = EEPROM.at25sf161ChipErase(); // Complete erase chip
  if(ret == 1)
  {
    Serial.println("[INFO] chip erase done at spi3.");
  }
  
  EEPROM.at25sf161ReadEeprom(readData, 512, 0x0); // read first 512 bytes of data.
  
  Serial.println();
  Serial.println("at25sf161 read data :");
  for(int i = 0; i < 512; i++)
  {
    if(i % 32 == 0)
      Serial.println();
    Serial.print(readData[i], HEX);
    Serial.print("  ");
  }
  Serial.println();
  
  int j = 128;
  for(int i = 0; i < 128; i++)
  {
    writeData[i] = i;
  }

  EEPROM.at25sf161WriteEeprom(writeData, 128, 0x0);   // writing data in page 1. Max length for write is 256 (page size).

  for(int i = 0; i < 128; i++)
  {
    writeData[i] = j;
    j--;
  }
  EEPROM.at25sf161WriteEeprom(writeData, 128, 0x100); // writing data in page 2.
  EEPROM.at25sf161ReadEeprom(readData, 512, 0x0); // read first 512 bytes of data.
  
  Serial.println();
  Serial.println("at25sf161 read data :");
  for(int i = 0; i < 512; i++)
  {
    if(i % 32 == 0)
      Serial.println();
    Serial.print(readData[i], HEX);
    Serial.print("  ");
  }
  Serial.println();

  while(1);
}
