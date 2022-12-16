#pragma once

//#define PLATFORM_NATIVE

//typedef unsigned char byte;

#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <cstring>
#include <stdarg.h>

#include "WCharacter.h"
#include "WString.h"


//#define DEC 10

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define LOW               0x0
#define HIGH              0x1

// GPIO FUNCTIONS
#define INPUT             0x01
// Changed OUTPUT from 0x02 to behave the same as Arduino pinMode(pin, OUTPUT) 
// where you can read the state of pin even when it is set as OUTPUT
#define OUTPUT            0x03 
#define PULLUP            0x04
#define INPUT_PULLUP      0x05
#define PULLDOWN          0x08
#define INPUT_PULLDOWN    0x09
#define OPEN_DRAIN        0x10
#define OUTPUT_OPEN_DRAIN 0x12
#define ANALOG            0xC0

// Interrupt Modes
#define DISABLED  0x00
#define RISING    0x01
#define FALLING   0x02
#define CHANGE    0x03
#define ONLOW     0x04
#define ONHIGH    0x05
#define ONLOW_WE  0x0C
#define ONHIGH_WE 0x0D



#define sq(x) ((x)*(x))

#define bit(b) (1UL << (b))



uint32_t millis();
uint32_t micros();
void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);

#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)

bool pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);

void analogReadResolution(int resolution_bits);
int analogRead(uint8_t pin);
void terminate();



void randomSeed(uint32_t seed);
//float random();

#include <cstdlib>
static inline long random(long v)
{
	return rand() % v;
}

static inline long random(long min, long max)
{
	return rand() % (max - min + 1) + min;
}

#ifndef __attribute__
	#define __attribute__(...)
#endif 


#ifndef F
//Define macro for strings stored in flash.
#define F(str) (str)
#endif  // F


void yield();



#include "Print.h"
#include "Stream.h"
#include "Printable.h"



#define RTC_DATA_ATTR
#define RTC_NOINIT_ATTR
#define DMA_ATTR


#include "./pgmspace.h"
