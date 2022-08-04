#ifndef __VEGA_SPI_H_
#define __VEGA_SPI_H_

/**
 @file spi_aries.h
 @brief header file for SPI driver
 @detail 
 */
/***************************************************
 * Module name: spi_aries.h
 *
 * Copyright 2020 Company CDAC(T).
 * All Rights Reserved.
 *
 *  The information contained herein is confidential
 * property of Company. The user, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Company.
 *
 *
 * Module Description:
 * SPI registers and function declarations
 *
 ***************************************************/

/*  Include section
 *
 ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"

/*  Define section
 *
 *
 ***************************************************/
// SPIs
#define SPI0                        0
#define SPI1                        1
#define SPI2                        2

// Register offsets
#define SPIM_CR                     0x00                    // Control Register
#define SPIM_SR                     0x04                    // Status Register
#define SPIM_BRR                    0x08                   // Baud Rate Register
#define SPIM_TDR                    0x0C                    // Transmit Data Register
#define SPIM_RDR                    0x10                   // Receive Data Register

// Fields
#define SPIM_CR_DBITS(x)            (((x) & 0xf) << 9)      // Bits per transfer
#define SPIM_CR_CSAAT               (0x1 << 8)              // Chip Select Active After Transfer
#define SPIM_CR_SPTIE(x)            (((x) & 0x1) << 7)      // SPI Transmit Interrupt Enable
#define SPIM_CR_SPRIE(x)            (((x) & 0x1) << 6)      // SPI Receive Interrupt Enable      

#define SPIM_CLK_CONFI_MODE(x)      (((x) & 0x3) << 4)      // SPI Clock configuration Modes
#define SPIM_SCK_MODE               (0x3 << 4)

#define SPIM_CR_LSBMSB(x)           (((x) & 0x1) << 3)      // This bit selects LSB/MSB first data transfer format.
#define SPIM_CR_PS(x)               (((x) & 0x1) << 2)      // Fixed peripheral-0  Variable peripheral-1
#define SPIM_CR_PCS(x)              ((x) & 0x3)             // Peripheral Chip select

#define SPIM_SR_TXE                 (1 << 7)                // Transmit data register empty
#define SPIM_SR_RXC                 (1 << 6)                // SPI Receive Complete
#define SPIM_SR_OVERR               (1 << 5)                // Overrun Error
#define SPIM_SR_TXB                 (1 << 4)                // Transmitter busy
#define SPIM_SR_TXINT               (1 << 3)                // Transmit hold register empty interrupt
#define SPIM_SR_RXINT               (1 << 2)                // Receive complete interrupt

#define SPIM_BRR_VALUE(x)           (((x) & 0xf) << 4)      // Baud rate register value

#define SPIM_TDR_CS0(x)             (((x) & 0x1) << 16)     // Slave Select bits in variable peripheral mode
#define SPIM_TDR_CS1(x)             (((x) & 0x1) << 17)
#define SPI_TDR_CSMODE(x)           (((x) & 0x3) << 16)

#define SPIM_RDR_CS0(x)             (((x) & 0x1) << 16)
#define SPIM_RDR_CS1(x)             (((x) & 0x1) << 17)
#define SPI_RDR_CSMODE(x)           (((x) & 0x3) << 16)

// Data transfer to slave
#define SPIM_TDR_DATA(x)            ((x) & 0xff)

// Data receive from slave
#define SPIM_RDR_DATA(x)            ((x) & 0xff)

// Status register
#define SPI_TXFIFO_FULL             (1 << 7)   
#define SPI_TXFIFO_EMPTY            (1 << 7)

#define SPI_RXNEW_DATA              (1 << 6)
#define SPI_NOTRXNEW_DATA           (1 << 6)

// Values
#define SPI_MSB_FIRST               0
#define SPI_LSB_FIRST               1

#define SPI_INTERRUPT_DISABLE       0
#define SPI_INTERRUPT_ENABLE        1

#define FIXED_PERIPHERAL            0
#define VARIABLE_PERIPHERAL         1

#define SPI_CSMODE_AUTO             0
#define SPI_CSMODE_HOLD             2
#define SPI_CSMODE_OFF              3

#define SPI_DIR_RX                  0
#define SPI_DIR_TX                  1

#define SPI_PROTO_S                 0
#define SPI_PROTO_D                 1
#define SPI_PROTO_Q                 2

// Data Bits Per Transfer
#define DBITS_8                     0
#define DBITS_9                     1
#define DBITS_10                    2
#define DBITS_11                    3
#define DBITS_12                    4
#define DBITS_13                    5
#define DBITS_14                    6
#define DBITS_15                    7
#define DBITS_16                    0x8

// Baudrate
#define SPI_BAUD_CFD_4        		0
#define SPI_BAUD_CFD_8        		1 
#define SPI_BAUD_CFD_16        		2 
#define SPI_BAUD_CFD_32        		3
#define SPI_BAUD_CFD_64        		4
#define SPI_BAUD_CFD_128        	5 
#define SPI_BAUD_CFD_256       		6
#define SPI_BAUD_CFD_512        	7 
#define SPI_BAUD_CFD_1024        	8 
#define SPI_BAUD_CFD_2048        	9

#define SPI_CLOCK_DIV4  0



/*  Function declaration section
 *
 *
 ***************************************************/
void SPI_Transmit(u_int8_t bData);
uint16_t SPI_Receive(void);


#endif   /* __VEGA_SPI_H_ */