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

// This includes all interrupts, like Watchdog Timer and
// Real-Time Clock, not just external interrupts.
static voidFuncPtr callbacksInt[6];


/* Configure I/O interrupt sources */
static void __initialize()
{
  // Clear out all the callback registers
  memset(callbacksInt, 0, sizeof(callbacksInt));

  // PLIC Registers are not eset in general. Clear
  // them out.
 /* PLIC_init(&g_plic,
	    PLIC_BASE_ADDR,
	    PLIC_NUM_INTERRUPTS,
	    PLIC_NUM_PRIORITIES);*/

  // Set the global PLIC interrupt.
  set_csr(mie, MIP_MEIP);

}

/*
 * \brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs.
 *        Replaces any previous function that was attached to the interrupt.
 */
void attachInterrupt(uint32_t intnum, voidFuncPtr callback, uint32_t mode)
{
 
  
  }
  

/*
 * \brief Turns off the given interrupt.
 */
void detachInterrupt(uint32_t intnum)
{
  

}


/*Entry Point for PLIC Interrupt Handler*/
void handle_m_ext_interrupt(){
  
}

/* TODO: Entry Point for Timer Interrupt Handler*/
void handle_m_time_interrupt() {

  // Does nothing for now.
  
}

uintptr_t handle_trap(uintptr_t mcause, uintptr_t epc)
{
}
