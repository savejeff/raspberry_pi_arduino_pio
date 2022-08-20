
#include "main.h"

#ifdef ENABLE_MAIN_ARDUINO_GPIO

#include "Arduino.h"

#define PIN_LED 20
#define PIN_BUTTON 21

void setup() {
	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_BUTTON, INPUT_PULLUP);

}

void loop() {

	int v = digitalRead(PIN_BUTTON);

	if(v)
	{
		digitalWrite(PIN_LED, HIGH);
	}
	else
	{
		digitalWrite(PIN_LED, LOW);
	}

	delay(100);

	if(millis() > 10 * 1000)
		terminate();
}

#endif // ENABLE_MAIN_ARDUINO_GPIO