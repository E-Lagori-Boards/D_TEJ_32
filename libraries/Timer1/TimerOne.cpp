/*
 */

#include "TimerOne.h"
#include "Arduino.h"
#include "wiring_private.h"
#include "encoding.h"
#include <string.h>

//TimerOne Timer1(1);              // preinstatiate

extern volatile unsigned int INTERRUPT_Handler_0;
extern volatile fp irq_table[64]; //Array of Function pointer.

unsigned short TimerOne::pwmPeriod = 0;
unsigned char TimerOne::clockSelectBits = 0;
volatile unsigned int TimerOne::isrCallbackAddr = 0;
unsigned int TimerOne::reload_cycles = 0;

TimerOne::TimerOne(uint32_t _id) :
		id(_id) {

}

// interrupt service routine that wraps a user defined function supplied by attachInterrupt

void TimerOne::isr_timer(void) {	// intr handler

	volatile void (*timerIsrCallback)();

	volatile unsigned int EOI = TIMER_REG(id, TIMER_REG_EOI);//clear timer interrupt
	volatile unsigned int istatus = TIMER_REG(id, TIMER_REG_IntrStatus);//clear timer interrupt

	Serial.println("istatus:");
	Serial.print(istatus, 16);

	//TIMER_REG(id,TIMER_REG_Control) = 0x0;	// Disable timer.

	timerIsrCallback = (fp) isrCallbackAddr;

	timerIsrCallback();

	//TIMER_REG(id,TIMER_REG_LoadCount) = 150000000;	// Load timer with no of clocks.
	//TIMER_REG(id,TIMER_REG_Control) = 0x3;	// Enable timer.

}

//****************************
//  Configuration
//****************************
void TimerOne::initialize(unsigned int microseconds) {

	setPeriod(microseconds);
}

void TimerOne::setPeriod(unsigned int microseconds) {
	unsigned int cycles = microseconds * ratio;

	reload_cycles = cycles;

	if (cycles > 0xffffffff)
		Serial.println("timer not supported for this value");

	Serial.println("TIMER_REG_LoadCount");
	Serial.print((unsigned int) (&TIMER_REG(id, TIMER_REG_LoadCount)), 16);
	Serial.print("\n");
	Serial.println("TIMER_REG_CurrentValue");
	Serial.print((unsigned int) (&TIMER_REG(id, TIMER_REG_CurrentValue)), 16);
	Serial.print("\n");
	Serial.println("TIMER_REG_Control");
	Serial.print((unsigned int) (&TIMER_REG(id, TIMER_REG_Control)), 16);
	Serial.print("\n");
	Serial.println("TIMER_REG_EOI");
	Serial.print((unsigned int) (&TIMER_REG(id, TIMER_REG_EOI)), 16);
	Serial.print("\n");
	Serial.println("TIMER_REG_IntrStatus");
	Serial.print((unsigned int) (&TIMER_REG(id, TIMER_REG_IntrStatus)), 16);

	Serial.println("press  key    ");
	Serial.read();

	TIMER_REG(id,TIMER_REG_Control) = 0x0;	// Disable timer.
	TIMER_REG(id,TIMER_REG_LoadCount) = cycles;	// Load timer with no of clocks.

}

//****************************
//  Run Control
//****************************
void TimerOne::start() {
	TIMER_REG(id,TIMER_REG_Control) = 0x03;	// Enable timer with intr unmasked.
}
void TimerOne::stop() {
	TIMER_REG(id,TIMER_REG_Control) = 0x0;		// Disable timer.
}
void TimerOne::restart() {
	TIMER_REG(id,TIMER_REG_Control) = 0x03;	// Enable timer with intr unmasked.
}
void TimerOne::resume() {
	TIMER_REG(id,TIMER_REG_Control) = 0x03;	// Enable timer with intr unmasked.
}

//****************************
//  Interrupt Function
//****************************

void TimerOne::attachInterrupt(void (*isr)(), unsigned long microseconds) {
	if (microseconds > 0)
		setPeriod(microseconds);
	attachInterrupt(isr);

}
void TimerOne::detachInterrupt() {
	TIMER_REG(id,TIMER_REG_Control) = 0x0;		// Disable timer.

	MACHINE_INT_ENABLE &= ~((unsigned int) (1 << (7 + id)));// Enable interrupt for peripheral in interrupt controller.
}

/*
 * \brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs.
 *        Replaces any previous function that was attached to the interrupt.
 */

void TimerOne::attachInterrupt(void (*user_isr)()) {

	unsigned int intr_number = (7 + id);

	// Should be enableInterrupt()
	// *************************Interrupt Enable*************************** //
	set_csr(mie, MIP_MEIP);	// Set MEIE bit in MIE register for Machine External Intr.
	set_csr(mstatus, MSTATUS_MIE);// Set global machine intr bit (3rd bit) in MSTATUS register.
	write_csr(mtvec, (uint32_t) (&INTERRUPT_Handler_0));// Set MTVEC register with vector address.
	MACHINE_INT_ENABLE |= ((unsigned int) (1 << intr_number));// Enable interrupt for peripheral in interrupt controller.

	Serial.println("MACHINE_INT_ENABLE:");
	Serial.print(MACHINE_INT_ENABLE, 16);
	Serial.read();

	// *************************Register IRQ Handler*************************** //

	irq_table[intr_number] = (fp) (&isr_timer);

	isrCallbackAddr = user_isr;

	TIMER_REG(id,TIMER_REG_Control) = 0x03;	// Enable timer with intr unmasked.
}
