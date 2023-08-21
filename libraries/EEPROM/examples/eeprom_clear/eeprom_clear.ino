/*
 @file   eeprom_clear.ino
 @brief  clear internal flash 
 @detail Sets all of the bytes of the EEPROM to 0.
 *       Please see eeprom_iteration for a more in depth
 *       look at how to traverse the EEPROM.  

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * NOTE : - VEGA ARIES Boards have 2MB flash i.e 2000000 Bytes. From which
 *          256KB is reserved as program memory.
*/

#include <EEPROM.h>

void setup() {
  EEPROM.begin();
  
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  // turn the LED on when we're done
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  /** Empty loop. **/
}
