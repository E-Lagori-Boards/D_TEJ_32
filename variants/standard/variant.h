#ifndef _VARIANT_FREEDOM_E300_
#define _VARIANT_FREEDOM_E300_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//#include "spi_aries.h"

#define SIFIVE_FREEDOM_E300_PLATFORM
#define FREEDOM_E300
#define RISCV
#include "platform.h"

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "Arduino.h"
#ifdef __cplusplus
#include "UARTClass.h"
#endif

#ifdef __cplusplus
extern UARTClass Serial;
extern UARTClass uart;

#endif

/*
 * SPI Interfaces
 */

#define SPI_INTERFACES_COUNT 4
#define IIC_INTERFACES_COUNT 2
#define UART_INTERFACES_COUNT 3

#define SPI_REG(id, offset) ((id==0)?SPI0_REG(offset):(id==1)?SPI1_REG(offset):(id==2)?SPI2_REG(offset):(id==3)?SPI3_REG(offset):SPI0_REG(offset))

#define IIC_REG(id, offset) ((id==0)?IIC0_REG(offset):(id==1)?IIC1_REG(offset):IIC0_REG(offset))

#define UART_REG(id, offset) ((id==0)?UART0_REG(offset):(id==1)?UART1_REG(offset):(id==2)?UART2_REG(offset):UART0_REG(offset))

#endif
