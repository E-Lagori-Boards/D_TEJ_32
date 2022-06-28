#include "Arduino.h"
#include "wiring_analog.h"
#include "platform.h"

__BEGIN_DECLS

static int _readResolution = 10;
static int _writeResolution = 8;

static uint8_t pwm_enabled[5];
static int8_t pwm_enabled_pin[5];

void analogReadResolution(int res) {
	_readResolution = res;
}

void analogWriteResolution(int res) {
	_writeResolution = res;
}

void analogWritePhase(uint32_t pin, uint32_t phase)
{
  int8_t pwm_num;
  
  if(pin >= variant_pin_map_size)
    return;

  pwm_num = variant_pin_map[pin].pwm_num;
  if(pwm_num > variant_pwm_size)
    {
      //TODO -- Not sure what this function is supposed to
      //        do exactly
    }
}
      
void analogOutputInit( void )
{
}


void analogWrite(uint32_t pin, uint32_t ulValue)
{


}

// FE300 Does not have analog inputs
uint32_t analogRead(uint32_t pin)
{
  return 0;
}

__END_DECLS
