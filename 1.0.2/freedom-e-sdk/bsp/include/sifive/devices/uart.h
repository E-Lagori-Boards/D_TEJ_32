// See LICENSE for license details.

#ifndef _SIFIVE_UART_H
#define _SIFIVE_UART_H

//UARTs
#define UART0                        0
#define UART1                        1
#define UART2                        2
#define UART3                        3

//#define UART0_BASE_ADDR 0x10000100// _AC(0x10000100,UL)
// #define UART1_BASE_ADDR _AC(0x10000200,UL)
// #define UART2_BASE_ADDR _AC(0x10000300,UL)

/* Register offsets */
#define	UART_REG_DR  		0x00	//UART Data register
#define UART_REG_IE 		0x04	//UART Interrupt enable register
#define	UART_REG_IIR_FCR 	0x08	//UART Interrupt identification(Read only), FIFO control register(write only).
#define	UART_REG_LCR 		0x0C	//UART Line control register
#define	UART_REG_LSR 		_AC(0x14,UL) //UART Line status register



/*fields*/
#define UART_LSR_DR			    (1)			//Data Ready
#define UART_LSR_THRE			(1 << 5)    //Transmitter Holding Register
#define UART_LSR_TEMT			(1 << 6)	//Transmitter Empty
	

/*
// Register offsets 
#define UART_REG_TXFIFO         0x00
#define UART_REG_RXFIFO         0x04
#define UART_REG_TXCTRL         0x08
#define UART_REG_RXCTRL         0x0c
//#define UART_REG_IE             0x10
#define UART_REG_IP             0x14
#define UART_REG_DIV            0x18

// TXCTRL register 
#define UART_TXEN               0x1
#define UART_TXWM(x)            (((x) & 0xffff) << 16)

// RXCTRL register 
#define UART_RXEN               0x1
#define UART_RXWM(x)            (((x) & 0xffff) << 16)

// IP register 
#define UART_IP_TXWM            0x1
#define UART_IP_RXWM            0x2
*/
#endif /* _SIFIVE_UART_H */
