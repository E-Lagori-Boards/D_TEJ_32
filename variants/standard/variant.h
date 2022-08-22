#ifndef _VARIANT_FREEDOM_E300_
#define _VARIANT_FREEDOM_E300_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARIES_v2_0
#define VEGA_PROCESSOR
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

#define UART_INTERFACES_COUNT 1
#define UART_REG(x) UART0_REG(x)
#define UART_REGP(i) _REG32P(UART0_BASE_ADDR, (i))
#define SPI_REG(id, offset) ((id==0)?SPI0_REG(offset):(id==1)?SPI1_REG(offset):(id==2)?SPI2_REG(offset):(id==3)?SPI3_REG(offset):SPI0_REG(offset))
#define IIC_REG(offset) IIC0_REG(offset)
#define IIC_REGP(i) _REG32P(IIC0_BASE_ADDR, (i))

#endif 
