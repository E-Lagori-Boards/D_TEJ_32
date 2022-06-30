// See LICENSE for license details.

#ifndef _SIFIVE_PLATFORM_H
#define _SIFIVE_PLATFORM_H

// Some things missing from the official encoding.h
#define MCAUSE_INT         0x80000000
#define MCAUSE_CAUSE       0x7FFFFFFF



/****************************************************************************
 * Platform definitions
 *****************************************************************************/
//#define UART_REG(x) UART0_REG(x)

// /* Register offsets */
// #define	UART_REG_DR  		0x00	//UART Data register
// #define UART_REG_IE 		0x04	//UART Interrupt enable register
// #define	UART_REG_IIR_FCR 	0x08	//UART Interrupt identification(Read only), FIFO control register(write only).
// #define	UART_REG_LCR 		0x0C	//UART Line control register
// #define	UART_REG_LSR 		0x14	//UART Line status register

#define TRAPVEC_TABLE_BASE_ADDR 0x00001010
#define CLINT_BASE_ADDR 0x02000000
#define PLIC_BASE_ADDR 0x0C000000
#define AON_BASE_ADDR 0x10000000
#define GPIO_BASE_ADDR 0x10080000
#define UART0_BASE_ADDR 0x10000100
#define SPI0_BASE_ADDR 0x10000600
#define PWM0_BASE_ADDR 0x10015000
#define GPI1_BASE_ADDR 0x10180000
#define UART1_BASE_ADDR 0x10000200
#define SPI1_BASE_ADDR  0x10000700
#define PWM1_BASE_ADDR 0x10025000
#define SPI2_BASE_ADDR 0x10200100
#define PWM2_BASE_ADDR 0x10035000
#define SPI0_MMAP_ADDR 0x20000000
#define MEM_BASE_ADDR 0x80000000
#define UART2_BASE_ADDR 0x10000300

// IOF Mappings
#define IOF0_SPI1_MASK          0x000007FC
#define SPI11_NUM_SS     (4)
#define IOF_SPI1_SS0          (2u)
#define IOF_SPI1_SS1          (8u)
#define IOF_SPI1_SS2          (9u)
#define IOF_SPI1_SS3          (10u)
#define IOF_SPI1_MOSI         (3u)
#define IOF_SPI1_MISO         (4u)
#define IOF_SPI1_SCK          (5u)
#define IOF_SPI1_DQ0          (3u)
#define IOF_SPI1_DQ1          (4u)
#define IOF_SPI1_DQ2          (6u)
#define IOF_SPI1_DQ3          (7u)

#define IOF0_SPI2_MASK          0xFC000000
#define SPI2_NUM_SS       (1)
#define IOF_SPI2_SS0          (26u)
#define IOF_SPI2_MOSI         (27u)
#define IOF_SPI2_MISO         (28u)
#define IOF_SPI2_SCK          (29u)
#define IOF_SPI2_DQ0          (27u)
#define IOF_SPI2_DQ1          (28u)
#define IOF_SPI2_DQ2          (30u)
#define IOF_SPI2_DQ3          (31u)

#define IOF0_UART0_MASK         0x00030000, UL)
#define IOF_UART0_RX   (16u)
#define IOF_UART0_TX   (17u)

#define IOF0_UART1_MASK         0x03000000, UL)
#define IOF_UART1_RX (24u)
#define IOF_UART1_TX (25u)

#define IOF1_PWM0_MASK          0x0000000F, UL)
#define IOF1_PWM1_MASK          0x00780000, UL)
#define IOF1_PWM2_MASK          0x00003C00, UL)
// New
#define UART_LSR_DR			    (1)			//Data Ready
#define UART_LSR_THRE			(1 << 5)    //Transmitter Holding Register
#define UART_LSR_TEMT			(1 << 6)	//Transmitter Empty

// Interrupt Numbers
#define INT_RESERVED 0
#define INT_WDOGCMP 1
#define INT_RTCCMP 2
#define INT_UART0_BASE 3
#define INT_UART1_BASE 4
#define INT_SPI0_BASE 5
#define INT_SPI1_BASE 6
#define INT_SPI2_BASE 7
#define INT_GPIO_BASE 8
#define INT_PWM0_BASE 40
#define INT_PWM1_BASE 44
#define INT_PWM2_BASE 48

// Helper functions
#define _REG32(p, i) (*((volatile unsigned int *) (p+ i)))
#define _REG32P(p, i) ((volatile unsigned int *) (p + i))
#define AON_REG(offset) _REG32(AON_BASE_ADDR, offset)
#define CLINT_REG(offset) _REG32(CLINT_BASE_ADDR, offset)
#define GPIO_REG(offset) _REG32(GPIO_BASE_ADDR, offset)
#define OTP_REG(offset)  _REG32(OTP_BASE_ADDR, offset)
#define PLIC_REG(offset) _REG32(PLIC_BASE_ADDR, offset)
#define PRCI_REG(offset) _REG32(PRCI_BASE_ADDR, offset)
#define PWM0_REG(offset) _REG32(PWM0_BASE_ADDR, offset)
#define PWM1_REG(offset) _REG32(PWM1_BASE_ADDR, offset)
#define PWM2_REG(offset) _REG32(PWM2_BASE_ADDR, offset)
#define SPI0_REG(offset) _REG32(SPI0_BASE_ADDR, offset)
#define SPI1_REG(offset) _REG32(SPI1_BASE_ADDR, offset)
#define SPI2_REG(offset) _REG32(SPI2_BASE_ADDR, offset)
#define UART0_REG(offset) _REG32(UART0_BASE_ADDR, offset)
#define UART1_REG(offset) _REG32(UART1_BASE_ADDR, offset)

// Misc

#include <stdint.h>


#define NUM_GPIO 32

#define PLIC_NUM_INTERRUPTS 52
#define PLIC_NUM_PRIORITIES 7

#define HAS_BOARD_BUTTONS


unsigned long get_timer_freq(void);
uint64_t get_timer_value(void);

#endif /* _SIFIVE_PLATFORM_H */
