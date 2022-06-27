#ifndef __VEGA_SPI_H_
#define __VEGA_SPI_H_

#include <stdio.h>
#include <stdlib.h>
#include "spi_aries.h"
#include "/home/himanshu/snap/arduino/61/.arduino15/packages/sifive/hardware/riscv/1.0.2/freedom-e-sdk/bsp/env/freedom-e300-arty/platform.h"
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
#define SPIM_CR_CSAAT(x)            (((x) & 0x1) << 8)      // Chip Select Active After Transfer
#define SPIM_CR_SPTIE(x)            (((x) & 0x1) << 7)      // SPI Transmit Interrupt Enable
#define SPIM_CR_SPRIE(x)            (((x) & 0x1) << 6)      // SPI Receive Interrupt Enable
#define SPIM_CR_CPOL(x)             (((x) & 0x1) << 5)      // Clock Polarity
#define SPIM_CR_CPHA(x)             (((x) & 0x1) << 4)      // Clock Phase

#define SPIM_CR_SCKMODE(x)          (((x) & 0x3) << 4)

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
// #define SPI_RDR_CSMODE              (SPIM_TDR_CS0(x) && SPIM_TDR_CS1(x))

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

#define REGISTER_NOT_EMPTY          0
#define REGISTER_EMPTY              1

#define RECEPTION_NOT_COMPLETED     0
#define NEW_DATA_AVAILABLE          1

#define NO_OVERRUN_ERROR            0
#define OVERRUN_ERROR               1

#define TRANSMIT_IDLE               0
#define TRANSMIT_BUSY               1

// #define SPI_BASE_ADDR(i) (((i) == 0 || (i) == 1) ? 0x10000600UL : 0x10000700UL)  //0x10200100UL
// #define SPI_REG(i) (*((volatile SPIregType *)(SPI_BASE_ADDR(i) + (0x100 * (i % 2)))))

#define SPI_CSMODE_AUTO             0
#define SPI_CSMODE_HOLD             2
#define SPI_CSMODE_OFF              3

#define SPI_DIR_RX                  0
#define SPI_DIR_TX                  1

#define SPI_PROTO_S                 0
#define SPI_PROTO_D                 1
#define SPI_PROTO_Q                 2

//For multiple bytes transfer
#define READ_EEPROM                 0x03     // Read Array


#endif

