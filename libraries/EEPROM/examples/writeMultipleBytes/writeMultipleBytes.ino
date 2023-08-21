/*
 @file   writeMultipleBytes.ino
 @brief  The demo to write multiple bytes of data on EEPROM. 
 @detail In this example, we are reading 256 bytes of data and display
 *       it on serial monitor.  

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * Note: VEGA ARIES Board has in-built flash of 2MB, You can read 
 *       upto 512 bytes at a time.
*/

#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  EEPROM.begin();

  uint8_t buffer[256];
  
  for(int i=0; i<256; i++) {
    buffer[i] = i;
  }
  Serial.print("Writing data on EEPROM.....");
  // we can write 256 bytes of data at a time
  EEPROM.write(buffer, 256, 0); // writebuffer, length, starting address
  Serial.println("done.");
  // turn the LED on when we're done
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  /** Empty loop. **/
}
