/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

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

#include "Arduino.h"
#include "wiring_private.h"
#include "encoding.h"

#include <string.h>


fp irq_table[64]; //Array of Function pointer.
fp sw_irq_function; //Software IRQ Function pointer.
extern volatile unsigned long INTERRUPT_Handler_0;
extern volatile unsigned long trap_entry;



// This includes all interrupts, like Watchdog Timer and
// Real-Time Clock, not just external interrupts.
// static voidFuncPtr callbacksInt[6];  ////////////////////////////////////////// warning: 'callbacksInt' defined but not used [-Wunused-variable]


/* Configure I/O interrupt sources */   ////////////////////////////////////////// warning: '__initialize' defined but not used [-Wunused-function]
// static void __initialize()
// {
//   // Clear out all the callback registers
//   memset(callbacksInt, 0, sizeof(callbacksInt));

//   // PLIC Registers are not eset in general. Clear
//   // them out.
//  /* PLIC_init(&g_plic,
// 	    PLIC_BASE_ADDR,
// 	    PLIC_NUM_INTERRUPTS,
// 	    PLIC_NUM_PRIORITIES);*/

//   // Set the global PLIC interrupt.
//   set_csr(mie, MIP_MEIP);

// }

/*
 * \brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs.
 *        Replaces any previous function that was attached to the interrupt.
 */
void attachInterrupt(uint8_t intr_number, void (*irq_handler)(), uint32_t mode) {
	// Should be enableInterrupt()
  // *************************Interrupt Enable*************************** //
  set_csr(mie, MIP_MEIP);			// Set MEIE bit in MIE register for Machine External Intr.
  set_csr(mstatus, MSTATUS_MIE);		// Set global machine intr bit (3rd bit) in MSTATUS register.
  write_csr(mtvec,(uint32_t)&INTERRUPT_Handler_0);		// Set MTVEC register with vector address.
  MACHINE_INT_ENABLE |= ((unsigned long)1 << intr_number);	// Enable interrupt for peripheral in interrupt controller.
	__asm__ __volatile__ ("fence");
  
  // *************************Register IRQ Handler*************************** //
  irq_table[intr_number] = irq_handler;
}

/*
 * \brief Turns off the given interrupt.
 */
void detachInterrupt(uint32_t intr_number) {
	// Should be disableInterrupt()
  MACHINE_INT_ENABLE |= ((unsigned long)0 << intr_number);
}
  

/*Entry Point for PLIC Interrupt Handler*/
void handle_m_ext_interrupt(){
  
}

/* TODO: Entry Point for Timer Interrupt Handler*/
void handle_m_time_interrupt() {

  // Does nothing for now.
  
}

// uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)  /////////////////////////////// Cause warnings
// {
  
// }

void interrupt_handler(void) {

	void (*func_ptr)();
	int mcause_val = 0, trap_type=0;

  trap_type = (read_csr(mcause) >> 31);



	if(trap_type){ //Interrupt

		mcause_val = ((read_csr(mcause) << 1)>>1);

		if(mcause_val == 3) {// Machine software interrupt
			clear_csr(mip, MIP_MSIP);	// Clear MSIP bit in MIP register for Machine 
			sw_irq_function(); // Invoke the peripheral handler as function pointer.	
		} else {
		
			unsigned long intr_status = MACHINE_INT_STATUS; // Read interrupt status register.

			for(unsigned long i = 0; i < MAXIMUM_INTR_COUNT ; i++)  /*MAXIMUM_INTR_COUNT*/
			{
				if ((intr_status >> i) & (unsigned long)1){			
					irq_table[i]();// Invoke the peripheral handler as function pointer.			
				}
			}
		}
	}
	else
	{ //Exception
		func_ptr = (void (*)()) (&trap_entry); //jump to exception handler
		func_ptr();
	}	
}
