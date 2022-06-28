
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
#endif

/*
 * SPI Interfaces
 */

#define SPI_INTERFACES_COUNT 1
#define SPI_REG(offset) SPI1_REG(offset)
#define SPI_REGP(i) _REG32P(SPI1_BASE_ADDR, (i))
// #define SPI_REG(x) SPI1_REG(x)

#define UART_INTERFACES_COUNT 1
#define UART_REG(x) UART0_REG(x)
#define UART_REGP(i) _REG32P(UART0_BASE_ADDR, (i))


#endif 
