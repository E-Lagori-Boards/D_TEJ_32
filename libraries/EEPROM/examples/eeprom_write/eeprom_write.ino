/*
 @file   eeprom_write.ino
 @brief  write data into internal flash via SPI 
 @detail Stores values read from analog input 0 into the EEPROM.
 *       These values will stay in the EEPROM when the board is
 *       turned off and may be retrieved later by another sketch.  

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * NOTE : - VEGA ARIES Boards have 2MB flash i.e 2000000 Bytes. From which
 *          256KB is reserved as program memory.
 *        - We can write upto 256 bytes at a time.
*/

#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int addr = 0;

void setup() {
  /** Empty setup. **/
  EEPROM.begin();
}

void loop() {
  /***
    Need to divide by 8 because analog inputs range from
    0 to 2048 and each byte of the EEPROM can only hold a
    value from 0 to 255.
  ***/

  int val = analogRead(0) / 8;
  Serial.println(val);
  /***
    Write the value to the appropriate byte of the EEPROM.
    these values will remain there when the board is
    turned off.
  ***/

  EEPROM.write(addr, val);

  // Advance to the next address, when at the end restart at the beginning.
  addr = addr + 1;
  if (addr == EEPROM.length()) {
    addr = 0;
  }

  delay(100);
}
