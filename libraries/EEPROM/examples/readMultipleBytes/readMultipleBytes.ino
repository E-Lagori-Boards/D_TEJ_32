/*
 @file   readMultipleBytes.ino
 @brief  The demo to read multiple bytes of data from EEPROM. 
 @detail In this example, we are writing 256 bytes of data 0n EEPROM  

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * Note: VEGA ARIES Board has in-built flash of 2MB, You can write 
 *       upto 256 bytes at a time.
*/

#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);

  uint8_t buffer[256];

  Serial.print("Reading data from EEPROM.....");
  // we can read maximum of 512 bytes at a time
  EEPROM.read(buffer, 256, 0); // readbuffer, length, starting address
  
  Serial.println("done.");
  
  for(int i=0; i<256; i++) {
    if(i%8 == 0)Serial.println();
    Serial.print(buffer[i]); Serial.print("     ");
  }
}

void loop() {
  /** Empty loop. **/
}
