#ifdef VARIANTE_NATIVE_LINUX

#include "Arduino.h"

#include <lgpio.h>

#ifdef ENABLE_ARDUINO_DEBUG
#define LogX printf
#else
#define LogX(...)
#endif

/*
#define LG_SET_ACTIVE_LOW  4
#define LG_SET_OPEN_DRAIN  8
#define LG_SET_OPEN_SOURCE 16
#define LG_SET_PULL_UP     32
#define LG_SET_PULL_DOWN   64
#define LG_SET_PULL_NONE   128
*/

static int h = -1;

static bool init_gpio()
{
	if(h < 0)
	{
		h = lgGpiochipOpen(0);
		if(h < 0)
		{
			LogX("gpio.err: init failed\n");
			return false;
		}
		return true;
	}
	else
		return true;
}

/******************** PUBLIC FUNCTIONS *************************/


bool GPIO_begin()
{
	return init_gpio();
}

void GPIO_end()
{
	if(h >= 0)
		lgGpiochipClose(h);
}


/*
Supported Modes:

#define INPUT             0x01
#define OUTPUT            0x03 
#define INPUT_PULLUP      0x05
#define INPUT_PULLDOWN    0x09
#define OPEN_DRAIN        0x10
#define OUTPUT_OPEN_DRAIN 0x12 (same as OPEN_DRAIN)
*/
bool pinMode(uint8_t pin, uint8_t mode)
{
	if(!init_gpio())
		return false;

	if(mode == OUTPUT)
	{
		return lgGpioClaimOutput(h, 0, pin, 0) == LG_OKAY;
	}
	if(mode == OPEN_DRAIN || mode == OUTPUT_OPEN_DRAIN)
	{
		return lgGpioClaimOutput(h, LG_SET_OPEN_DRAIN, pin, 0) == LG_OKAY;
	}
	if(mode == INPUT)
	{
		return lgGpioClaimInput(h, 0, pin) == LG_OKAY;
	}
	if(mode == INPUT_PULLUP)
	{
		return lgGpioClaimInput(h, LG_SET_PULL_UP, pin) == LG_OKAY;
	}
	if(mode == INPUT_PULLDOWN)
	{
		return lgGpioClaimInput(h, LG_SET_PULL_DOWN, pin) == LG_OKAY;
	}

	LogX("gpio.err: pin mode %d not supported", mode);
	return false;
}

void digitalWrite(uint8_t pin, uint8_t val)
{
	if(!init_gpio())
		return;

	lgGpioWrite(h, pin, val);
}

int digitalRead(uint8_t pin)
{
	if(!init_gpio())
		return -1;

	return lgGpioRead(h, pin);
}


void analogReadResolution(int resolution_bits)
{
	// not supported
}

int analogRead(uint8_t pin)
{
	return 0;
}

#endif // VARIANTE_NATIVE_LINUX