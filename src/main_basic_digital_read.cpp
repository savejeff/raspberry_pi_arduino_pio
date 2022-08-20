#include "main.h"
#ifdef ENABLE_MAIN_BASIC_DIGITAL_READ

#include "Arduino.h"

#include <lgpio.h>

int h;

#define PIN_IN 21



/*
#define LG_SET_ACTIVE_LOW  4
#define LG_SET_OPEN_DRAIN  8
#define LG_SET_OPEN_SOURCE 16
#define LG_SET_PULL_UP     32
#define LG_SET_PULL_DOWN   64
#define LG_SET_PULL_NONE   128
*/

//#define LFLAGS 0
#define LFLAGS LG_SET_PULL_UP

int main()
{
	printf("____Start____\n");

	h = lgGpiochipOpen(0);
	if(h < 0)
	{
		printf("gpio.err: init failed");
		return 0;
	}

	if (lgGpioClaimInput(h, LFLAGS, PIN_IN) == LG_OKAY)
	{

		for (int i = 0; i < 10 * 4; i++)
		{
			int v = lgGpioRead(h, PIN_IN);
			printf("gpio.in: pin%d=%d\n", PIN_IN, v);
			delay(250);
		}
	}

	lgGpiochipClose(h);

	printf("____End____\n");

}

#endif // ENABLE_MAIN_BASIC_DIGITAL_READ