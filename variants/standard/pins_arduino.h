// API compatibility
#include "variant.h"

#define PINS_COUNT    (40u)

#define NINA_CTS      NINA_ACK
#define NINA_RTS      NINA_GPIO0

#define PIN_LED_22  (22)
#define PIN_LED     PIN_LED_22
#define LED_BUILTIN PIN_LED

//NINA
#define NINA_GPIO0  (17) //connect 27-GPIO0 (Boot pin) of WiFiNINA to GPIO13 of Aries V2 or GPIO17 of Aries IOT
#define NINA_RESETN (27u)  //Not using
#define NINA_ACK    (28u)   //Not using

#define SS_FLASHMEM 1

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (-1)
#define PIN_SPI_MISO  (-1)
#define PIN_SPI_SCK   (-1)
#define SDCARD_SS_PIN (10)

// attachInterrupt()
#define digitalPinToInterrupt(p) ((p) >= 0 && (p) <= 11 ? (p) + 10 : NOT_AN_INTERRUPT)

static const uint8_t SS   = PIN_SPI_SS;
// static const uint8_t CS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// WiFiNINA
#define regtype volatile uint32_t
#define regsize uint32_t
