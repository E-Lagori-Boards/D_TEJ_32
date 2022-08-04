/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UARTClass.h"

#include "variant.h"
#include "platform.h"
void* __dso_handle;

UARTClass Serial;

// Public Methods //

void UARTClass::sio_setbaud(int bauds)
{

  unsigned long divisor;
  UART_REG(UART_REG_LCR) = 0x83;	//setting DLAB = 1 in LCR
  divisor = (F_CPU / (bauds * 16));
  UART_REG( UART_REG_DR) = divisor & 0xFF;	//to get LSB only AND with FF
  UART_REG( UART_REG_IE) = (divisor >> 0x08) & 0xFF;	//to get MSB only
  UART_REG( UART_REG_LCR) = 0x03;	//Clearing DLAB in LCR
  UART_REG(UART_REG_IE) = 0x00;
 
}


void UARTClass::begin( unsigned long bauds)
{

	  unsigned long divisor;
	  divisor = (F_CPU / (bauds * 16));
	  UART_REG( UART_REG_LCR )= 0x83; //0x83
	  UART_REG( UART_REG_DR) = divisor & 0xFF;	//LSB//0x28
	  UART_REG( UART_REG_IE) = (divisor >> 0x08) & 0xFF;	//MSB//0x00
	  UART_REG( UART_REG_LCR) = 0x03;	//set DLAB to 0
	  UART_REG( UART_REG_IE) = 0x00;
	  UART_REG( UART_REG_IIR_FCR) = 0x00;
	  __asm__ __volatile__ ("fence");

}

int UARTClass::sio_getchar(int c) //c-The variable to hold the read character
{

  while ((UART_REG(UART_REG_LSR) & UART_LSR_DR) != UART_LSR_DR);  //waiting for Data Ready
  c = UART_REG( UART_REG_DR);
  return c;
}


int UARTClass::sio_putchar(char c)	//write
{

  while ((UART_REG(UART_REG_LSR) & UART_LSR_THRE) != UART_LSR_THRE);	//waiting for THRE to be empty
  UART_REG(UART_REG_DR) = c;
  return 0;
}


int UARTClass::read(void)
{

  return (sio_getchar(1));
}


size_t UARTClass::write(const uint8_t uc_data)
{

  sio_putchar(uc_data);
  return (1);
}