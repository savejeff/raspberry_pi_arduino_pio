#pragma once

#include "Arduino.h"


#define SPI_FRQ_10MHz 10E6
#define SPI_FRQ_8MHz 8E6
#define SPI_FRQ_7MHz 7E6
#define SPI_FRQ_4MHz 4E6
#define SPI_FRQ_1MHz 1E6
#define SPI_FRQ_500kHz 500E3
#define SPI_FRQ_100kHz 100E3
#define SPI_FRQ_10kHz 10E3

#define SPI_FRQ_DEFAULT SPI_FRQ_500kHz

enum SPI_BitOrder {
	SPI_BitOrder_LSBFIRST = 0,
	SPI_BitOrder_MSBFIRST = 1
};


//Mode          Clock Polarity (CPOL)   Clock Phase (CPHA)
	//SPI_MODE0             0                     0
	//SPI_MODE1             0                     1
	//SPI_MODE2             1                     0
	//SPI_MODE3             1                     1
enum SPI_DATAMODE {
	SPI_DATAMODE0 = 0x00,
	SPI_DATAMODE1 = 0x01,
	SPI_DATAMODE2 = 0x02,
	SPI_DATAMODE3 = 0x03
};

class SPIClass
{
protected:

    int spi_dev_num;  // SPI Device Number (0 or 1)
	int spi_channel; // SPI spi_channel (0 = SPIX_CE0, 1 = SPIX_CE1)
	int speed = 50000;   // SPI bps
	int flags = SPI_DATAMODE0;   // SPI flags
	SPI_BitOrder bitorder = SPI_BitOrder_MSBFIRST;
	int spih = -1;    // SPI handle


public:
	SPIClass(uint8_t spi_num, uint8_t spi_cs_num=0)
    : spi_dev_num(spi_num), spi_channel(spi_cs_num)
    {

    }

	void begin();
	void end();

	virtual bool beginTransaction(uint32_t _freq = SPI_FRQ_DEFAULT, SPI_BitOrder _bitOrder = SPI_BitOrder_MSBFIRST, SPI_DATAMODE _dataMode = SPI_DATAMODE0);
	virtual void endTransaction(void);
	virtual void transfer(uint8_t * data, uint32_t size);
	virtual uint8_t transfer(uint8_t data);

	// sets the spi channel (pin 0, pin 1) or software pins (pin >= 2)
	virtual void init_CS(uint8_t pin);
	// use this to manually set Chip select (only works with software pins)
	virtual void setCS(uint8_t pin, bool state);

protected:

	
};


extern SPIClass SPI;
