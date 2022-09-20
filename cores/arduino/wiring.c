/*-
 * Copyright (c) 2015 Marko Zec, University of Zagreb
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 */

#include "Arduino.h"
#include "platform.h"
#include "encoding.h"

unsigned long clock_count;


unsigned long millis() {
  static uint8_t count;
  unsigned long current_clock_count;

  count = count + 1;

  if(count <= 1)
  {
    clock_count = read_csr(mcycle);
    return ((clock_count * 0.0135)/1000);
  }
  else
  {
    current_clock_count = read_csr(mcycle);
    return (((current_clock_count - clock_count) * 0.0135)/1000);
  }
}


unsigned long micros(void) {

  static uint8_t count;
  unsigned long current_clock_count = 0;

  count = count + 1;

  if(count <= 1)
  {
    clock_count = read_csr(mcycle);
    return (clock_count * 0.0135);
  }
  else
  {
    current_clock_count = read_csr(mcycle);
    return ((current_clock_count - clock_count) * 0.0135);
  }
}


void delay(unsigned long  ms) {

  unsigned long  cycle_count, current_cycle, target_cycle;

  cycle_count = ms * SYS_FREQ * 1000 * 1.85;

  current_cycle = read_csr(mcycle);
  target_cycle = current_cycle + cycle_count;

  while ((read_csr(mcycle) < target_cycle))
    ;
}

void delayMicroseconds(unsigned long us) {

  unsigned int cycle_count, current_cycle, target_cycle;

  cycle_count = us * SYS_FREQ * 1.85;

  current_cycle = read_csr(mcycle);
  target_cycle = current_cycle + cycle_count;

  while ((read_csr(mcycle) < target_cycle))
    ;
}