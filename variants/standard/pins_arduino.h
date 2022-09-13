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

// #define SS 1
#define SS_FLASHMEM 1

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (16)
#define PIN_SPI_MISO  (14)
#define PIN_SPI_SCK   (15)
#define SDCARD_SS_PIN (10)

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;