// API compatibility
#include "variant.h"

#define PINS_COUNT    (40u)

#define NINA_CTS      NINA_ACK
#define NINA_RTS      NINA_GPIO0

#define PIN_LED_13  (13u)
#define PIN_LED     PIN_LED_13
#define LED_BUILTIN PIN_LED

//NINA
#define NINA_GPIO0  (13) //connected to GPIO13 of aries
#define NINA_RESETN (27u)  //Not using
#define NINA_ACK    (28u)   //Not using

#define SS 1
#define SS_FLASHMEM 1