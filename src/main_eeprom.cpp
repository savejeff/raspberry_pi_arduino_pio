
#include "main.h"

#ifdef ENABLE_MAIN_EEPROM

#include "Arduino.h"

#include "EEPROM.h"

uint8_t counter = 0;
#define ADDRESS_COUNTER 0x00

void setup() {
	EEPROM.begin();

    // load previous counter value
    counter = EEPROM.read(ADDRESS_COUNTER);

    printf("start counter: %d\n", counter);
}

void loop() {

    // increase counter by 1
    counter++;
    
    // write counter to eeprom
    EEPROM.write(ADDRESS_COUNTER, counter);
    
    // commit to make permanent
    EEPROM.commit();

    printf("counter: %d\n", counter);

    delay(1000);

    // stop after 10s
    if(millis() > 10 * 1000)
        terminate();
}

#endif // ENABLE_MAIN_EEPROM