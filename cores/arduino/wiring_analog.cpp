#include "Arduino.h"
#include "wiring_analog.h"
#include "platform.h"
#include "pwm.h"
#include "utility/twi.h"
#include "Wire.h"

// extern PWMClass PWM;
// extern TwoWire Wire;


void analogWrite(uint32_t pin, uint32_t ulValue)
{
  //PWM.PWMC_Set_Period(pin, 800000);
  PWM.PWMC_Set_OnOffTime(pin, ulValue*2000);
  PWM.PWMC_init(pin);
  PWM.PWMC_Enable(pin);
}



static void writeRegister(uint8_t address, uint8_t reg, uint16_t value) {

	Wire.beginTransmission(address);
	Wire.write((uint8_t) reg);
	Wire.write((uint8_t) (value >> 8));
	Wire.write((uint8_t) (value & 0xFF));
	Wire.endTransmission(TRUE);
}

static uint16_t readRegister(uint8_t address, uint8_t reg) {

	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.endTransmission(TRUE);
	Wire.requestFrom(address, (uint8_t) 2);	//true
	return (Wire.read() << 8 | Wire.read());
}

float analogRead(uint32_t pin)
{
	Wire.begin(); //need to check
	if (pin > 3) {	//channel=pin
		return 1;
	}

	// Start with default values
	uint16_t config = ADS1015_REG_CONFIG_CQUE_NONE |// Disable the comparator (default val)
			ADS1015_REG_CONFIG_CLAT_NONLAT |  // Non-latching (default val)
			ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
			ADS1015_REG_CONFIG_CMODE_TRAD | // Traditional comparator (default val)
			ADS1015_REG_CONFIG_DR_3300SPS |	  // 3300 samples per second
			ADS1015_REG_CONFIG_MODE_SINGLE;	  // Single-shot mode (default)

	// Set PGA/voltage range
	config |= ADS1015_REG_CONFIG_PGA_4_096V;

	// Set single-ended input channel
	switch (pin) {
	case (0):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
		break;
	case (1):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
		break;
	case (2):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
		break;
	case (3):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
		break;
	}

	// Set 'start single-conversion' bit
	config |= ADS1015_REG_CONFIG_OS_SINGLE;

	// Write config register to the ADC
	writeRegister(ADS1015_ADDRESS, ADS1015_REG_POINTER_CONFIG, config);

	// Wait for the conversion to complete
	delayMicroseconds(ADS1015_CONVERSIONDELAY);

	// Read the conversion results
	// Shift 12-bit results right 4 bits for the ADS1015
	float resolution = 0.002;
	uint16_t adc_value = readRegister(ADS1015_ADDRESS, ADS1015_REG_POINTER_CONVERT)>> BIT_SHIFT;
	return (adc_value*resolution);

	//return 0;
}
