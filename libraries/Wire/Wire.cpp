/*
 TwoWire.cpp - TWI/I2C library for Wiring & Arduino
 Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
 Modified 2017 by Chuck Todd (ctodd@cableone.net) to correct Unconfigured Slave Mode reboot
 Modified 2020 by Greyson Christoforo (grey@christoforo.net) to implement timeouts
 */

extern "C" {
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "utility/twi.h"
}

#include "Wire.h"

// Initialize Class Variables //////////////////////////////////////////////////

uint8_t TwoWire::rxBuffer[BUFFER_LENGTH];
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;

uint8_t TwoWire::slaveAddress = 0;
uint8_t TwoWire::txBuffer[BUFFER_LENGTH];
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;

uint8_t TwoWire::transmitting = 0;

uint8_t DataRead;

// Constructors ////////////////////////////////////////////////////////////////

TwoWire::TwoWire() {
}

// Public Methods //////////////////////////////////////////////////////////////

void TwoWire::begin(void) {
	rxBufferIndex = 0;
	rxBufferLength = 0;
	txBufferIndex = 0;
	txBufferLength = 0;

	IIC_REG(IIC_REG_TxCLR) = 0xFF; //clear TxFIFO register
	__asm__ __volatile__ ("fence");
	unsigned short CH = SYS_CLK / (2 * I2C_CLK); //sys clock=75000000, i2c clock=100000
	IIC_REG(IIC_REG_CHL) = ((unsigned char) (CH & 0x0FF)); //set timing registers CHL,CHH,CHHL,CHHH
	IIC_REG(IIC_REG_CHH) = (unsigned char) ((CH >> 8) & 0xFF);
	unsigned short CHH = SYS_CLK / (4 * I2C_CLK);
	IIC_REG(IIC_REG_CHHL) = ((unsigned char) (CHH & 0xFF));
	IIC_REG(IIC_REG_CHHH) = (unsigned char) ((CHH >> 8) & 0xFF);
	__asm__ __volatile__ ("fence");

}

void TwoWire::begin(uint8_t address) {
	begin();
}

void TwoWire::begin(int address) {
	begin((uint8_t) address);
}

void TwoWire::setClock(uint32_t clock) {
	clock = I2C_CLK;
	unsigned short CH = SYS_CLK / (2 * I2C_CLK); //sys clock=75000000, i2c clock=100000
	IIC_REG(IIC_REG_CHL) = ((unsigned char) (CH & 0x0FF)); //set timing registers CHL,CHH,CHHL,CHHH
	IIC_REG(IIC_REG_CHH) = (unsigned char) ((CH >> 8) & 0xFF);
	unsigned short CHH = SYS_CLK / (4 * I2C_CLK);
	IIC_REG(IIC_REG_CHHL) = ((unsigned char) (CHH & 0xFF));
	IIC_REG(IIC_REG_CHHH) = (unsigned char) ((CHH >> 8) & 0xFF);
	__asm__ __volatile__ ("fence");

}

/***
 * Sets the TWI timeout.
 *
 * This limits the maximum time to wait for the TWI hardware. If more time passes, the bus is assumed
 * to have locked up (e.g. due to noise-induced glitches or faulty slaves) and the transaction is aborted.
 * Optionally, the TWI hardware is also reset, which can be required to allow subsequent transactions to
 * succeed in some cases (in particular when noise has made the TWI hardware think there is a second
 * master that has claimed the bus).
 *
 * When a timeout is triggered, a flag is set that can be queried with `getWireTimeoutFlag()` and is cleared
 * when `clearWireTimeoutFlag()` or `setWireTimeoutUs()` is called.
 *
 * Note that this timeout can also trigger while waiting for clock stretching or waiting for a second master
 * to complete its transaction. So make sure to adapt the timeout to accommodate for those cases if needed.
 * A typical timeout would be 25ms (which is the maximum clock stretching allowed by the SMBus protocol),
 * but (much) shorter values will usually also work.
 *
 * In the future, a timeout will be enabled by default, so if you require the timeout to be disabled, it is
 * recommended you disable it by default using `setWireTimeoutUs(0)`, even though that is currently
 * the default.
 *
 * @param timeout a timeout value in microseconds, if zero then timeout checking is disabled
 * @param reset_with_timeout if true then TWI interface will be automatically reset on timeout
 *                           if false then TWI interface will not be reset on timeout

 */

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity,
		uint32_t iaddress, uint8_t isize, uint8_t sendStop) { //address = slave adress,quantity=num ofbytes
	return requestFrom((uint8_t) address, (uint8_t) quantity,
			(uint8_t) sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity,
		uint8_t sendStop) {
	rxBufferLength = quantity;
	IIC_REG(IIC_REG_CR ) = ((quantity << 2) | 0x01); //Set Start bit for read,set read length
	__asm__ __volatile__ ("fence");
	slaveAddress = ((address << 1) | IIC_READ);	//shift address to indicate R/W
	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxFFF)) == (IIC_SR0_TxFFF))
		; //TxFF full or not
	IIC_REG(IIC_REG_TxFF) = slaveAddress; //write slave address to Txff
	__asm__ __volatile__ ("fence");

	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxC)) != (IIC_SR0_TxC))
		; //Transmission is completed or not
	if (((IIC_REG(IIC_REG_SR1)) & (IIC_SR1_NACK)) == (IIC_SR1_NACK)) { //checks NACK
		while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_STPS)) != (IIC_SR0_STPS))
			; //wait for stop bit to be set
		return 0;
	}
	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_RxC)) != (IIC_SR0_RxC))
		; //Rxc or not
	if (rxBufferLength > BUFFER_LENGTH) {
		Serial.print("data too long to fit in transmit buffer for read. \n\r");
		return 0;	//data too long to fit in transmit buffer.
	}
	for (int i = 0; i < rxBufferLength; i++) {
		while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_RxFFE)) == (IIC_SR0_RxFFE))
			; //check RxFF empty
		rxBuffer[i] = IIC_REG(IIC_REG_RxFF); //read data from Rx register
	}
	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_STPS)) != (IIC_SR0_STPS))
		; //wait for stop bit to be set
	rxBufferIndex = 0;

	if (sendStop) {
		IIC_REG(IIC_REG_CR) = 0x02; 	//set stop bit
		__asm__ __volatile__ ("fence");
		while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_STPS)) != (IIC_SR0_STPS))
			; //check stop sequence initiated

	}
	return rxBufferLength;
	//return requestFrom((uint8_t) address, (uint8_t) quantity, (uint32_t) 0,
	//		(uint8_t) 0, (uint8_t) sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop) {

	return requestFrom((uint8_t) address, (uint8_t) quantity,
			(uint8_t) sendStop);
}

void TwoWire::beginTransmission(uint8_t address) {

	// indicate that we are transmitting
	transmitting = 1;
	// set address of targeted slave
	slaveAddress = (address << 1) | IIC_WRITE;	//shift address to indicate R/W
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
	IIC_REG(IIC_REG_TxCLR) = 0xFF;		//clear TxFifo
	while ((((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxFFE)) != (IIC_SR0_TxFFE))
			|| (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxC)) != (IIC_SR0_TxC)))
		;		//checks for transmission complete and TxFifo empty
	IIC_REG(IIC_REG_CR) = 0x01;		//Set Start bit for write
	__asm__ __volatile__ ("fence");
	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_STAS)) != (IIC_SR0_STAS))
		;		//check start sequence initiated

}

void TwoWire::beginTransmission(int address) {
	beginTransmission((uint8_t) address);
}

//	Originally, 'endTransmission' was an f(void) function.
//	It has been modified to take one parameter indicating
//	whether or not a STOP should be performed on the bus.
//	Calling endTransmission(false) allows a sketch to
//	perform a repeated start.
//
//	WARNING: Nothing in the library keeps track of whether
//	the bus tenure has been properly ended with a STOP. It
//	is very possible to leave the bus in a hung state if
//	no call to endTransmission(true) is made. Some I2C
//	devices will behave oddly if they do not see a STOP.
//
uint8_t TwoWire::endTransmission(uint8_t sendStop) {
	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxFFF)) == (IIC_SR0_TxFFF))
		; //TxFF full or not
	IIC_REG(IIC_REG_TxFF) = slaveAddress; //write slave address to Txff
	// slaveAddress++;
	__asm__ __volatile__ ("fence");
	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxC)) != (IIC_SR0_TxC))
		;		//Transmission is completed or not

	if (((IIC_REG(IIC_REG_SR1)) & (IIC_SR1_NACK)) == (IIC_SR1_NACK)) { //checks NACK

		while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_STPS)) != (IIC_SR0_STPS))
			;			//wait for stop bit to be set
		return 2;			//received NACK on transmit of address.
	}

	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxFFF)) == (IIC_SR0_TxFFF))
		;			//TxFF full or not
	if (txBufferLength > BUFFER_LENGTH) {
		Serial.print("data too long to fit in transmit buffer in write. \n\r");
		return 1;	//data too long to fit in transmit buffer.
	}

	for (int i = 0; i < txBufferLength; i++) {

		IIC_REG(IIC_REG_TxFF) = txBuffer[i];//data of write stored in buffer in write()
		//	Serial.print(IIC_REG(IIC_REG_TxFF));

		while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxC)) != (IIC_SR0_TxC))
			;			//Transmission is completed or not

		if (((IIC_REG(IIC_REG_SR1)) & (IIC_SR1_NACK)) == (IIC_SR1_NACK)) { //checks NACK
			Serial.print("NACK rxd and stop bit set in write \n\r");
			while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_STPS)) != (IIC_SR0_STPS))
				; //wait for stop bit to be set
			return 3;				// received NACK on transmit of data.
		}
	}

	IIC_REG(IIC_REG_CR) = 0x02; //Set Stop bit;
	__asm__ __volatile__ ("fence");
	while (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_STPS)) != (IIC_SR0_STPS))
		; //check stop sequence initiated

	if (sendStop == false) {
		transmitting = 1;
		// reset tx buffer iterator vars
		txBufferIndex = 0;
		txBufferLength = 0;
		IIC_REG(IIC_REG_TxCLR) = 0xFF;		//clear TxFifo
		while ((((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxFFE)) != (IIC_SR0_TxFFE))
				|| (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_TxC)) != (IIC_SR0_TxC)))
			;		//checks for transmission complete and TxFifo empty

		__asm__ __volatile__ ("fence");

	}

	txBufferIndex = 0;
	txBufferLength = 0;
	// indicate that we are done transmitting
	transmitting = 0;
	return 0;
}

//	This provides backwards compatibility with the original
//	definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void) {
	return endTransmission(true);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data) {
	//Serial.print("write start \n\r");

	if (txBufferIndex >= BUFFER_LENGTH) {
		Serial.print(
				"error, data size exceeded call end transmission() before more write()");
		setWriteError();
		return 0;
	}
// put byte in tx buffer
	txBuffer[txBufferIndex] = data;
	++txBufferIndex;
// update amount in buffer
	txBufferLength = txBufferIndex;
	return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity) {
	//Serial.print("write start1 \n\r");
	for (size_t i = 0; i < quantity; ++i) {
		write(data[i]);
	}
	return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void) {

	//if (((IIC_REG(IIC_REG_SR0)) & (IIC_SR0_RxFFE)) == (IIC_SR0_RxFFE)) {//check RxFF empty
	return rxBufferLength;
	//Serial.print("rxBufferLength \n\r");

}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void) {

	int value = -1;

	// get each successive byte on each call
	if (rxBufferLength > 0) {
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
		rxBufferLength--;

	}
	return value;

}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void) {

}

void TwoWire::flush(void) {
// XXX: to be implemented.
}

void TwoWire::onRequestService(void) {

}

// sets function called on slave write
void TwoWire::onReceive(void (*function)(int)) {
	user_onReceive = function;
}

// sets function called on slave read
void TwoWire::onRequest(void (*function)(void)) {
	user_onRequest = function;
}

// Preinstantiate Objects //////////////////////////////////////////////////////
TwoWire Wire = TwoWire();
