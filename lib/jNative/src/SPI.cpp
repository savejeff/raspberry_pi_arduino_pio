#include "SPI.h"

#include <lgpio.h>


#ifdef ENABLE_ARDUINO_DEBUG
#define LogX printf
#else
#define LogX(...)
#endif

void SPIClass::begin() {
	spih = -1;
}

void SPIClass::end() {

}


bool SPIClass::beginTransaction(uint32_t _freq, SPI_BitOrder _bitOrder, SPI_DATAMODE _dataMode) {
	speed = _freq; // Test this
	bitorder = _bitOrder;
	flags = _dataMode;

	spih = lgSpiOpen(spi_dev_num, spi_channel, speed, flags);
	if(spih < 0)
	{
		return false;
	}

	return true;
}

void SPIClass::endTransaction(void) {
	if(spih >= 0)
	{
		lgSpiClose(spih);
		spih = -1;
	}
}

void SPIClass::transfer(uint8_t * data, uint32_t size) {
	if(spih < 0)
	{
		return;
	}

	lgSpiXfer(spih, (char*) data, (char*) data, size);
	
}

uint8_t SPIClass::transfer(uint8_t data) {
	if(spih < 0)
	{
		return 0xFF;
	}

	char buf[1];

	buf[0] = data;

	lgSpiXfer(spih, buf, buf, 1);

	return buf[0];
}

void SPIClass::init_CS(uint8_t pin) {
	if(pin < 2)
	{
		spi_channel = pin;
	}
	else
	{
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	}
}
void SPIClass::setCS(uint8_t pin, bool state) {
	if(pin >= 2)
		digitalWrite(pin, state);
}