#pragma once

#include "Arduino.h"

#ifndef I2C_BUFFER_LENGTH
	#define I2C_BUFFER_LENGTH 256
#endif // I2C_BUFFER_LENGTH

class TwoWire
{
protected:

    int bus;       // I2C bus
    int device = -1;    // I2C device address
    int flags = 0;     // I2C flags
    int i2ch = -1;      // I2C handle

	
	uint8_t buffer_rx[I2C_BUFFER_LENGTH];
	uint16_t buffer_rx_index;
	uint8_t buffer_tx[I2C_BUFFER_LENGTH];
	uint16_t buffer_tx_index;
	

public:
	TwoWire(uint8_t bus_id)
    : bus(bus_id)
    {

    }

	void begin();
	void end();

	// Set Bus Frequency
	//freq: [Hz] transmission frquency
	virtual void setClock(uint32_t freq) {
        // freq is fixed at boot time
        // edit to config.txt is needed
        // default is 100kHz
    }

	// Starts a I2C Transmission
	// addr: 7-bit address (shiften one left and added R/W bit internal)
	virtual bool beginTransmission(uint8_t addr);
	
	// End ongoing I2C Transmission
	// returns 0 is succesfull (ACK) | non-zero if error (NACK)
	virtual uint8_t endTransmission(bool stopBit);
    
	// End ongoing I2C Transmission with stopBit
	// returns 0 is succesfull (ACK) | non-zero if error (NACK)
	virtual uint8_t endTransmission(void) {
        return endTransmission(true);
    }

    // Requests Data to Read from I2C device 
	// https://www.arduino.cc/reference/en/language/functions/communication/wire/requestfrom/
	// address: the 7-bit slave address of the device to request bytes from.
	// quantity: the number of bytes to request.
	// stopBit: true will send a stop message after the request, releasing the bus. False will continually send a restart after the request, keeping the connection active.
	// returns the number of bytes returned from the peripheral device. (if buffered) if not buffered: returns requested quantity
	virtual uint8_t requestFrom(uint8_t address, size_t quantity, bool stopBit);
    virtual uint8_t requestFrom(uint8_t address, size_t quantity) {
        return requestFrom(address, quantity, true);
    }

	// Write/Send single byte
	// returns 1 if succesfull | 0 if failed
    virtual size_t write(uint8_t data);
    
	// Write/Send multiple bytes
	// returns amount of succesfull send bytes
	virtual size_t write(const uint8_t * data, size_t quantity);

	// Read single byte from I2C (from Device if not buffered, from Buffer if buffered)
	virtual uint8_t read(void);
	
	// Read multiple bytes from I2C Device. returns number of bytes received
	//virtual size_t read(uint8_t * data, size_t quantity);
	virtual void read(uint8_t * data, size_t quantity) {
		for(int i = 0; i < quantity; i++)
			data[i] = read();
	}

	
	// Returns number available bytes in RX Buffer (only works with buffered implementations)
	virtual uint16_t available();

	
	// read a 8bit register value from a 8bit address
	uint8_t read8_reg8(uint8_t device_addr, uint8_t reg)
	{ 
		uint8_t data = 0;
		
		this->beginTransmission(device_addr);
		this->write(reg);
		this->endTransmission(false);
		this->requestFrom(device_addr, 1);
		data = this->read();
		this->endTransmission();
		
		return data;
	}
	
	// read a 8bit register value from a 8bit address
	// returns true if transmission ok | false on error
	bool read8_reg8(uint8_t device_addr, uint8_t reg, uint8_t& data)
	{
		
		bool error = false;
		this->beginTransmission(device_addr);
		error |= this->write(reg) == 0;
		error |= this->endTransmission(false) != 0;
		error |= this->requestFrom(device_addr, 1) != 1;
		data = this->read();
		error |= this->endTransmission() != 0;
		
		return !error;
	}

	// write a 8bit register value to a 8bit address
	bool write8_reg8(uint8_t device_addr, uint8_t reg, uint8_t data) 
	{ 
		bool error = false;
		this->beginTransmission(device_addr);
		error |= this->write(reg) == 0;
		error |= this->write(data) == 0;
		error |= this->endTransmission() != 0;

		return !error;
	}

protected:

	// actual perform a write to i2c bus
	size_t _write(const uint8_t * data, size_t quantity);

	// actual perform a read to i2c bus
	size_t _read(uint8_t * data, size_t quantity);

};

extern TwoWire Wire;
