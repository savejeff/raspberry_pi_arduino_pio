#pragma once

/***************************************************************
 * 
 *  Uncomment only a single MAIN to switch between examples 
 *  otherwise multiple mains are defined
 * 
 * ************************************************************/

// Basic Code Examples to test low level code
//#define ENABLE_MAIN_BASIC_DIGITAL_WRITE
//#define ENABLE_MAIN_BASIC_DIGITAL_READ
//#define ENABLE_MAIN_BASIC_I2C_REG_WRITE_READ
//#define ENABLE_MAIN_BASIC_SPI_REG_WRITE_READ

// Arduino Like Code Examples
#define ENABLE_MAIN_ARDUINO

#ifdef ENABLE_MAIN_ARDUINO

    #define ENABLE_MAIN_EMPTY
    //#define ENABLE_MAIN_ARDUINO_GPIO
    //#define ENABLE_MAIN_ARDUINO_I2C
    //#define ENABLE_MAIN_ARDUINO_SPI
    //#define ENABLE_MAIN_ARDUINO_SPI_MAX31865

void terminate();

#endif // ENABLE_MAIN_ARDUINO
