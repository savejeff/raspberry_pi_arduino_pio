
#include "main.h"

#ifdef ENABLE_MAIN_BASIC

#include "Arduino.h"

void setup() {
	
}

void loop() {
    printf("Hallo World\n");
    delay(1000);

    if(millis() > 10000)
        terminate();
}

#endif // ENABLE_MAIN_BASIC