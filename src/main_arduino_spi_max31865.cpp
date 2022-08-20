#include "main.h"
#ifdef ENABLE_MAIN_ARDUINO_SPI_MAX31865

#include "Arduino.h"



#include <lgpio.h>

/*******************************************************************/

#define SPI_REG_RW 0x00

/*******************************************************************/

#include "SPI.h"

#define PIN_SPI_CS 22

SPIClass SPI(0, 0);

uint32_t spi_speed = 100000;
SPI_DATAMODE spi_mode = SPI_DATAMODE1;
SPI_BitOrder spi_bitorder = SPI_BitOrder_MSBFIRST;

/*******************************************************************/

void setup()
{
	printf("____Start____\n");

	printf("spi.state: begin\n");
	SPI.begin();

	SPI.init_CS(PIN_SPI_CS);
}

void loop() {

	static uint32_t loop_count = 0;
	loop_count++;

	if(false) { // single write and read 

		uint8_t data = loop_count;
		
		// Write register
		SPI.setCS(PIN_SPI_CS, LOW);
		SPI.beginTransaction(spi_speed, spi_bitorder, spi_mode);
		
		uint8_t data_rx = SPI.transfer(data);
		
		SPI.endTransaction();
		SPI.setCS(PIN_SPI_CS, HIGH);
		
		printf("spi.trans: tx=x%02X, rx=x%02X\n", data, data_rx);

	}

	if(true) { // write reg

		uint8_t reg = SPI_REG_RW;
		uint8_t val = loop_count % 2 ? 0x00 : 0x10;
		
		SPI.setCS(PIN_SPI_CS, LOW);
		SPI.beginTransaction(spi_speed, spi_bitorder, spi_mode);
		
		uint8_t buff[2];
		buff[0] = (reg & 0x7F) | 0x80;
		buff[1] = val;
		SPI.transfer(buff, 2);
		
		//buff[0] = SPI.transfer(buff[0]);
		//buff[1] = SPI.transfer(buff[1]);
		
		SPI.endTransaction();
		SPI.setCS(PIN_SPI_CS, HIGH);
		
		printf("spi.write: reg=x%02X, val=x%02X\n", reg, val);

	}

	if(true) { // read reg

		uint8_t reg = SPI_REG_RW;
		
		SPI.setCS(PIN_SPI_CS, LOW);
		SPI.beginTransaction(spi_speed, spi_bitorder, spi_mode);
		
		uint8_t buff[2];
		buff[0] = (reg & 0x7F) | 0x00;
		buff[1] = 0x00;
		SPI.transfer(buff, 2);

		//buff[0] = SPI.transfer(buff[0]);
		//buff[1] = SPI.transfer(buff[1]);
		
		uint8_t val = buff[1];

		SPI.endTransaction();
		SPI.setCS(PIN_SPI_CS, HIGH);
		
		printf("spi.read: reg=x%02X, val=x%02X\n", reg, val);

	}
	delay(1000);

	if(millis() > 10 * 1000)
	{
		printf("spi.state: end\n");
		SPI.end();

		printf("___ END __");
		terminate();
	}
}

#endif // ENABLE_MAIN_ARDUINO_SPI_MAX31865