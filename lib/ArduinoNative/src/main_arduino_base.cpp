#include "Arduino.h"

// Arduino GPIO functions
extern bool GPIO_begin();
extern void GPIO_end();

// Arduino Scetch function
extern void setup();
extern void loop();

static bool _terminate = false;

void terminate()
{
	_terminate = true;
}

int main()
{
	millis(); // this sets start time as millis = 0 reference

	GPIO_begin();

	setup();

	while(!_terminate)
		loop();

	GPIO_end();
}
