#include "Wire.h"

#include <lgpio.h>


#ifdef ENABLE_ARDUINO_DEBUG
#define LogX printf
#else
#define LogX(...)
#endif


void TwoWire::begin()
{
	i2ch = -1;
	device = -1;

	buffer_rx_index = 0;
	buffer_tx_index = 0;
}

void TwoWire::end() 
{
	if(i2ch >= 0)
	{
		lgI2cClose(i2ch);
		i2ch = -1;
	}
}

bool TwoWire::beginTransmission(uint8_t addr) {
	if(i2ch >= 0)
	{
		lgI2cClose(i2ch);
		i2ch = -1;
	}

	device = addr;
	
	i2ch = lgI2cOpen(bus, device, flags);
	if(i2ch < 0)
	{
		LogX("i2c.err: open failed\n");
		return false;
	}

	buffer_rx_index = 0;
	buffer_tx_index = 0;

	return true;
}

uint8_t TwoWire::endTransmission(bool stopBit) {

	// Write out TX Buffer
	if(buffer_tx_index > 0) {
		_write(buffer_tx, buffer_tx_index);
		buffer_tx_index = 0;
	}

	if(stopBit) {

		// close i2c connection
		if(i2ch >= 0)
		{
			lgI2cClose(i2ch);
			i2ch = -1;
		}

		// Clear RX Buffer
		buffer_tx_index = 0;
	}

	return 0;
}

uint8_t TwoWire::requestFrom(uint8_t address, size_t quantity, bool stopBit) 
{
	if(i2ch < 0)
	{
		return 0;
	}

	// avoid buffer overflow
	if(quantity > I2C_BUFFER_LENGTH)
	{
		LogX("i2c.warn: request higher quantity as rx buffer size. limit is %d\n", I2C_BUFFER_LENGTH);
		
		quantity = I2C_BUFFER_LENGTH;
	}

	buffer_rx_index = _read(buffer_rx, quantity);

	if(stopBit)
	{
		endTransmission();
	}

	return buffer_rx_index;
}

size_t TwoWire::write(uint8_t data) 
{
	if(buffer_tx_index < I2C_BUFFER_LENGTH)
	{
		buffer_tx[buffer_tx_index++] = data;
		return 1;
	}
	return 0;
}

size_t TwoWire::write(const uint8_t * data, size_t quantity) 
{
	for(int i = 0; i < quantity; i++)
	{
		if(buffer_tx_index < I2C_BUFFER_LENGTH)
		{
			buffer_tx[buffer_tx_index++] = data[i];
		}
		else
		{
			// buffer full
			return i;
		}
	}

	return quantity;
}

uint8_t TwoWire::read(void) 
{
	if(buffer_rx_index <= 0)
		return 0xFF;

	uint8_t val = buffer_rx[0];

	// shfit buffer content left by one byte (ineffcient)
	for(int i = 0; i < buffer_rx_index - 1; i++)
		buffer_rx[i] = buffer_rx[i + 1];
	buffer_rx_index--;

	return val;
}

/*
size_t TwoWire::read(uint8_t* data, size_t quantity) 
{
	
}
*/

uint16_t TwoWire::available() 
{
	if(i2ch < 0)
	{
		return 0;
	}

	return buffer_rx_index;
}


/******************************* Protected / Internal functions **********************/


size_t TwoWire::_write(const uint8_t * data, size_t quantity) 
{
	if(i2ch < 0)
	{
		return 0;
	}

	if(quantity == 0)
	{
		LogX("i2c.err: _write with len zero\n");
		return 0;
	}

	if(lgI2cWriteDevice(i2ch, (char*) data, quantity) == LG_OKAY)
		return quantity;

	LogX("i2c.err: _write failed\n");
	return 0;
}

size_t TwoWire::_read(uint8_t* data, size_t quantity) 
{
	if(i2ch < 0)
	{
		return 0;
	}

	return lgI2cReadDevice(i2ch, (char*) data, quantity);
}



TwoWire Wire(1);
