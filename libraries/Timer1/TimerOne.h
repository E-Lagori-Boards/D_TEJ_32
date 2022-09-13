/*
 */
#include "platform.h"
#include <WInterrupts.h>
#ifndef TimerOne_h_
#define TimerOne_h_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//#include "config/known_16bit_timers.h"


#define TIMER1_RESOLUTION 65536UL  // assume 16 bits for non-AVR chips

//UARTs
#define TIMER0                        0
#define TIMER1                        1
#define TIMER2                        2

//#define GPIO0 0
//#define GPIO1 1

/* Register offsets */
#define	TIMER_REG_LoadCount  		0x00	//Timer1 load count register
#define TIMER_REG_CurrentValue 		0x04	//Timer1 current value register
#define	TIMER_REG_Control 			0x08	//Timer1 control register
#define	TIMER_REG_EOI 				0x0C	//Timer1 end-of-interrupt register
#define	TIMER_REG_IntrStatus 		0x10 	//Timer1 interrupt status register

//#define	TIMER_REG_EOI 				0xA4	//TimerN end-of-interrupt register
//#define	TIMER_REG_IntrStatus 		0xA0 	//TimerN interrupt status register
//#define	TIMER_REG_RawIntrStatus 	0xA8 	//TimerN interrupt status register



// Placing nearly all the code in this .h file allows the functions to be
// inlined by the compiler.  In the very common case with constant values
// the compiler will perform all calculations and simply write constants
// to the hardware registers (for example, setPeriod).


class TimerOne
{

  public:
	TimerOne(uint32_t _id);
	//volatile uint32_t id;
    //****************************
    //  Configuration
    //****************************
    void initialize(unsigned int microseconds);
    void setPeriod(unsigned int microseconds);
	
    //****************************
    //  Run Control
    //****************************	
    void start();
    void stop();
    void restart();
    void resume();
	
    //****************************
    //  PWM outputs
    //****************************
	

    //****************************
    //  Interrupt Function
    //****************************
    void attachInterrupt(void (*isr)());
    void attachInterrupt(void (*isr)(), unsigned long microseconds);
    void detachInterrupt();
    void isr_timer(void);

  private:
    volatile uint32_t id;
    static unsigned short pwmPeriod;
    static unsigned char clockSelectBits;
    static volatile unsigned int isrCallbackAddr;
    static unsigned int reload_cycles;
    static const unsigned int ratio = (F_CPU)/ ( 1000000 );
    static fp sw_irq_function; //Software IRQ Function pointer.
};

extern TimerOne Timer1;

#endif

