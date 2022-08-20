#include "main.h"
#ifdef ENABLE_MAIN_BASIC_DIGITAL_WRITE

#include "Arduino.h"

#include <lgpio.h>

int h;

#define PIN_OUT 21

/*
#define LG_SET_ACTIVE_LOW  4
#define LG_SET_OPEN_DRAIN  8
#define LG_SET_OPEN_SOURCE 16
#define LG_SET_PULL_UP     32
#define LG_SET_PULL_DOWN   64
#define LG_SET_PULL_NONE   128
*/

#define LFLAGS 0

int main()
{
	printf("____Start____\n");

	h = lgGpiochipOpen(0);
	if(h < 0)
	{
		printf("gpio.err: init failed");
		return 0;
	}

	if (lgGpioClaimOutput(h, LFLAGS, PIN_OUT, 0) == LG_OKAY)
	{

		for (int i = 0; i < 10; i++)
		{
			printf("gpio.out: 0\n");
			lgGpioWrite(h, PIN_OUT, 0);
			delay(1000);
			
			printf("gpio.out: 1\n");
			lgGpioWrite(h, PIN_OUT, 1);
			delay(1000);
		}
	}

	lgGpiochipClose(h);

	printf("____End____\n");

}

#endif // ENABLE_MAIN_BASIC_DIGITAL_WRITE