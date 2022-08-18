/***************************************************************************
* Module name                           :  at25sf161.cpp
* Name of Author                        :  Himanshu Kishor Diwane, C-DAC
* Email ID  (Report any bugs)           :  kishor.dh@cdac.in
* Module Description                    :  AT25SF161 SPI Flash Library

  Copyright (C) 2020  CDAC(T). All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.

***************************************************************************/

/**
 @file at25sf161.cpp
 @brief AT25SF161 SPI Flash Library 
 @detail 
 */

/*  Include section
 *
 ***************************************************/
#include "at25sf161.h"

/*  Global variable section
 *
 ***************************************************/
SPIEeprom EEPROM;
extern SPIClass SPI;



/** 
 * @fn uint8_t *SPIEeprom::at25sf161Begin() 
 * @brief To initialize the at25sf161 eeprom.
 * @details 
 * @param[in] No input parameter
 * @param[Out] No output parameter 
*/
uint8_t *SPIEeprom::at25sf161Begin() {

	static unsigned char devID[3];

	SPI.begin(DBITS_8, SPI_MODE3, SPI_MSB_FIRST);
	SPI.setClockDivider(0);
	SPI.spiSlaveSelect();
	SPI.transfer(0x9F);
	SPI.transfer(devID, 3);
	SPI.spiSlaveDeselect();

	return devID;
}


/** 
 * @fn void SPIEeprom::at25sf161ReadEeprom(unsigned char *readBuf, unsigned long length, unsigned int eepromAddress)
 * @brief To read at25sf161 eeprom data.
 * @details 
 * @param[in] unsigned char *readBuf, unsigned long length, unsigned int eepromAddress
 * @param[Out] No output parameter 
*/
void SPIEeprom::at25sf161ReadEeprom(unsigned char *readBuf, unsigned long length, unsigned int eepromAddress) {
	
	unsigned char cmdBuf[4];
	
	cmdBuf[0] = READ_EEPROM;				  //read command.
	cmdBuf[1] = (eepromAddress >> 16) & 0xFF; // address bits 15-23
	cmdBuf[2] = (eepromAddress >> 8) & 0xFF;  // address bits  8-15
	cmdBuf[3] = (eepromAddress)&0xFF;		  // address bits  0-7


    SPI.spiSlaveSelect();

	// eeprom read command.
	SPI.transfer(cmdBuf, 4);
	// reading data.
	SPI.transfer(readBuf, length);
	SPI.spiSlaveDeselect();
}


/** 
 * @fn void SPIEeprom::at25sf161WriteEeprom(unsigned char *writeBuf, unsigned long length, unsigned int eepromAddress)
 * @brief To write data to at25sf161 eeprom.
 * @details 
 * @warning Max Write length should not be greater than page size (256).
 * @param[in] unsigned char *writeBuf, unsigned long length, unsigned int eepromAddress
 * @param[Out] No output parameter 
*/
void SPIEeprom::at25sf161WriteEeprom(unsigned char *writeBuf, unsigned long length, unsigned int eepromAddress) {

	unsigned char cmdBuf[4];

	if (length > PAGE_SIZE)
	{
		return;
	}

	cmdBuf[0] = WRITE_ENABLE;

	SPI.spiSlaveSelect();					// Setting CSAAT bit high.
	SPI.transfer(cmdBuf, 1);
	SPI.spiSlaveDeselect();					// Setting CSAAT bit low

	
	cmdBuf[0] = WRITE_EEPROM;				  // write command.
	cmdBuf[1] = (eepromAddress >> 16) & 0xFF; // address bits 15-23
	cmdBuf[2] = (eepromAddress >> 8) & 0xFF;  // address bits  8-15
	cmdBuf[3] = (eepromAddress)&0xFF;		  // address bits  0-7

    SPI.spiSlaveSelect();					// Setting CSAAT bit high.
	// eeprom read command.
	SPI.transfer(cmdBuf, 4);
	// reading data.
	SPI.transfer(writeBuf, length);  
	SPI.spiSlaveDeselect();					// Setting CSAAT bit low.
	at25sf161BusyWait();
}


/** 
 * @fn int SPIEeprom::at25sf161ChipErase(void)
 * @brief For compleate at25sf161 eeprom erase.
 * @details 
 * @param[in] No output parameter 
 * @param[Out] No output parameter 
*/
int SPIEeprom::at25sf161ChipErase(void) {

	static unsigned char opcode;

	SPI.spiSlaveSelect();					// Setting CSAAT bit high.
	opcode = WRITE_ENABLE;
	SPI.transfer(&opcode, 1);
	SPI.spiSlaveDeselect();					// Setting CSAAT bit low.

	SPI.spiSlaveSelect();
	opcode = CHIP_ERASE;
	SPI.transfer(&opcode, 1);
	SPI.spiSlaveDeselect();
	
	at25sf161BusyWait();
	return 1;
}


/** 
 * @fn void at25sf161BusyWait(void)
 * @brief Wait till at25sf161 eeprom is busy.
 * @details 
 * @param[in] No output parameter 
 * @param[Out] No output parameter 
*/
void at25sf161BusyWait(void) {
	
	static unsigned char status;
	SPI.spiSlaveSelect();
	do{
		SPI.transfer(READ_STATUS_1);
		SPI.transfer(&status, 1);
	}while(status & EEPROM_BUSY);
	SPI.spiSlaveDeselect();
}