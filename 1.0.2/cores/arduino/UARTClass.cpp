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



/*int UARTClass::sio_probe_rx()
{
  int32_t c;

  if ((c = UART_REG(UART_REG_RXFIFO)) >= 0) {
    sio_rxbuf[sio_rxbuf_head++] = c;
    sio_rxbuf_head &= SIO_RXBUFMASK;
    return(1);
  }
  return(0);
}*/


int
UARTClass::sio_getchar(int c)
{ 
	//c-The variable to hold the read character
  //volatile unsigned int *uart0_lsr_reg = UART_REGP(UART_REG_LSR);

  while ((UART_REG(UART_REG_LSR) & UART_LSR_DR) != UART_LSR_DR);	//waiting for Data Ready
  c = UART_REG( UART_REG_DR);
  return c;
}


// int UARTClass::sio_putchar(char c)	//write
// {
// 	volatile unsigned int *uart0_lsr_reg = UART_REGP(UART_REG_LSR);
  
//   while ((*uart0_lsr_reg & 0x20) != 0x20);	//waiting for THRE to be empty
//   UART_REG(UART_REG_DR) = c;


// 	return 0;
// }
int UARTClass::sio_putchar(char c)	//write
{
	//volatile unsigned int *uart0_lsr_reg = UART_REGP(UART_REG_LSR);
  
  while ((UART_REG(UART_REG_LSR) & 0x20) != 0x20);	//waiting for THRE to be empty
  UART_REG(UART_REG_DR) = c;


	return 0;
}
// int UARTClass::sio_putchar(char c)
// {

//   volatile unsigned int *uart0_lsr_reg = (volatile unsigned int *)0x10000114;

//   //while (((UART_REG(UART_REG_LSR) & 0x20) != 0x20) && (UART_REG_LSR & 0x40 != 0x40)); 

// do{


// if((*uart0_lsr_reg & 0x20) == 0x20)
// 	break;

// }while(1);

//   UART_REG(UART_LSR_DR) = c;
//   return 0;
// }

/*
 * Set RS-232 baudrate.  Works well with FT-232R from 300 to 3000000 bauds.
 */
void
UARTClass::sio_setbaud(int bauds)
{

  //F_Baud = f_in/(div+1) 
  
  unsigned long divisor;
  UART_REG(UART_REG_LCR) = 0x83;	//setting DLAB = 1 in LCR
  divisor = (F_CPU / (bauds * 16));
  UART_REG( UART_REG_DR) = divisor & 0xFF;	//to get LSB only AND with FF
  UART_REG( UART_REG_IE) = (divisor >> 0x08) & 0xFF;	////to get MSB only
  UART_REG( UART_REG_LCR) = 0x03;	//Clearing DLAB in LCR
  UART_REG(UART_REG_IE) = 0x00;

  //UART_REG(UART_REG_DIV) = F_CPU / bauds - 1;
 
}


// Public Methods //////////////////////////////////////////////////////////////

void
UARTClass::begin( unsigned long bauds)
{

unsigned long divisor; 
	  divisor = (F_CPU / (bauds * 16));
	  UART_REG( UART_REG_LCR )= 0x83; //0x83
	  UART_REG( UART_REG_DR) = 0x28;//divisor & 0xFF;	//LSB
	  UART_REG( UART_REG_IE) = 0x00;//(divisor >> 0x08) & 0xFF;	//MSB
	  UART_REG( UART_REG_LCR) = 0x03;	//set DLAB to 0
	  UART_REG( UART_REG_IE) = 0x00;
	  UART_REG( UART_REG_IIR_FCR) = 0x00;
	  __asm__ __volatile__ ("fence");

  /*GPIO_REG(GPIO_OUTPUT_XOR)&= ~(IOF0_UART0_MASK);
  GPIO_REG(GPIO_IOF_SEL)   &= ~(IOF0_UART0_MASK);
  GPIO_REG(GPIO_IOF_EN)    |= IOF0_UART0_MASK;

  //F_Baud = f_in/(div+1) 

  UART_REG(UART_REG_DIV) = F_CPU / bauds - 1;
  UART_REG(UART_REG_TXCTRL) |= UART_TXEN;
  UART_REG(UART_REG_RXCTRL) |= UART_RXEN;
*/
	
//  sio_setbaud(bauds);
}





/*void UARTClass::end(void)
{
  GPIO_REG(GPIO_IOF_EN)    &= ~IOF0_UART0_MASK;

  UART_REG(UART_REG_TXCTRL) &= ~UART_TXEN;
  UART_REG(UART_REG_RXCTRL) &= ~UART_RXEN;

}*/


/*int UARTClass::available(void)
{

  sio_probe_rx();
  return (!(sio_rxbuf_head == sio_rxbuf_tail));
}*/


/*int UARTClass::availableForWrite(void)
{
  int busy;
  busy = ((int32_t)UART_REG(UART_REG_TXFIFO) < 0);
  return (!busy);
}*/


/*int UARTClass::peek(void)
{
  sio_probe_rx();
  if (sio_rxbuf_tail == sio_rxbuf_head)
    return (-1);
  else
    return (sio_rxbuf[sio_rxbuf_tail]);
}*/


int UARTClass::read(void)
{

  return (sio_getchar(1));
}


/*void UARTClass::flush(void)
{
}*/


size_t UARTClass::write(const uint8_t uc_data)
{

  sio_putchar(uc_data);
  return (1);
}
