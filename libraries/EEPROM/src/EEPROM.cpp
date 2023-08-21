#include "Arduino.h"
#include "EEPROM.h"
#include "at25sf161.h"

EEPROMClass EEPROM;

EEPROMClass::EEPROMClass(void) {
    // starting address 0x00, first 256 Kilo-bytes are reserved as program memory
    // 256 KB is equal to 262144 Bytes in hexadecimal 0x40000
    _address = 0x40000;
}

/**
 * @fn void EEPROMClass::begin(void)
 * @brief To initialize eeprom.
 * @details
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void EEPROMClass::begin(void) {
    uint32_t address = _address;
    SPI_EEPROM.at25sf161Begin();
	for (int i = 0; i < 64; i++) { //earse 256K
		SPI_EEPROM.at25sf161blockErase4k(address);
		address += (4 * 1024);
	}
    return;
}

/**
 * @fn uint8_t EEPROMClass::read(uint32_t address)
 * @brief To read single byte data from eeprom.
 * @details
 * @param[in] unsigned int address : :  the location to read from, starting from 0 (int)
 * @param[Out] No output parameter
 * @return the value stored in that location (byte)
 */
uint8_t EEPROMClass::read(uint32_t address) {
    uint8_t data;
    SPI_EEPROM.at25sf161ReadEeprom(&data, 1, (_address + address));
    return data;
}

/**
 * @fn void EEPROMClass::read(uint8_t *readBuf, uint32_t length, uint32_t eepromAddress)
 * @brief To read multiple bytes at a time from eeprom.
 * @details
 * @param[in] uint32_t length : the length of data to be read in bytes(max 512 bytes) 
 *            uint32_t eepromAddress : Starting address (0 to onward)
 * @param[Out] uint8_t *readBuf
 * @return 
 */
void EEPROMClass::read(uint8_t *readBuf, uint32_t length, uint32_t eepromAddress) {
    SPI_EEPROM.at25sf161ReadEeprom(readBuf, length, (_address + eepromAddress));
    return;
}

/**
 * @fn void EEPROMClass::write(uint32_t address, uint8_t val)
 * @brief To write a data byte to eeprom.
 * @details
 * @param[in] uint32_t address : the location to write to, starting from 0 (int)
 *            uint8_t val : the value to write, from 0 to 255 (byte)
 * @param[Out] No output parameter
 */
void EEPROMClass::write(uint32_t address, uint8_t val) {
    SPI_EEPROM.at25sf161WriteEeprom(&val, 1, (_address + address));
    return;
}

/**
 * @fn void EEPROMClass::write(uint8_t *writeBuf, uint32_t length, uint32_t eepromAddress)
 * @brief To write multiple bytes at a time
 * @details
 * @param[in] uint32_t length : the length of data to be write (in bytes) (max 256 bytes) 
 *            uint32_t eepromAddress : Starting address (0 to onward)
 * @param[Out] uint8_t *writeBuf
 * @return 
 */
void EEPROMClass::write(uint8_t *writeBuf, uint32_t length, uint32_t eepromAddress) {
    SPI_EEPROM.at25sf161WriteEeprom(writeBuf, length, (_address + eepromAddress));
    return;
}

/**
 * @fn void EEPROMClass::update(uint32_t address, uint8_t val)
 * @brief To update a particular byte to eeprom.
 * @details Write a byte to the EEPROM. 
 * The value is written only if differs from the one already saved at the same address.
 * @param[in] uint32_t address : the location to write to, starting from 0 (int)
 *            uint8_t val : the value to write, from 0 to 255 (byte)
 * @param[Out] No output parameter
 * @return 
 */
void EEPROMClass::update(uint32_t address, uint8_t val) {
    uint8_t currentValue;
    SPI_EEPROM.at25sf161ReadEeprom(&currentValue, 1, (_address + address));

    if(currentValue == val)
        return;
        
    SPI_EEPROM.at25sf161WriteEeprom(&val, 1, (_address + address));
    return;
}

/**
 * @fn uint32_t EEPROMClass::length(void)
 * @brief This function returns an unsigned int containing the number of cells in the EEPROM.
 * @details
 * @param[in] 
 * @param[Out] 
 * @return Number of cells in the EEPROM as an unsigned int.
 */
uint32_t EEPROMClass::length(void) {
    return PAGE_SIZE;
}
