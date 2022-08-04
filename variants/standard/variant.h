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

extern uint32_t SPI_PORT;
/*
 * SPI Interfaces
 */

#define SPI_INTERFACES_COUNT 4


#define UART_INTERFACES_COUNT 1
#define UART_REG(x) UART0_REG(x)
#define UART_REGP(i) _REG32P(UART0_BASE_ADDR, (i))
#define SPI_REG(offset) SPIX_REG(SPI_PORT, offset)
#define SPIX_REG(x, offset) (((x)>=0&&(x)>=1)?((x)>=1&&(x)>=2)?((x)>=2&&(x)>=3)?SPI3_REG(offset):SPI2_REG(offset):SPI1_REG(offset):SPI0_REG(offset))

#define IIC_REG(offset) IIC0_REG(offset)
#define IIC_REGP(i) _REG32P(IIC0_BASE_ADDR, (i))

#endif 
