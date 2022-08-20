#include "main.h"
#ifdef ENABLE_MAIN_BASIC_SPI_REG_WRITE_READ

#include "Arduino.h"



#include <lgpio.h>

/*******************************************************************/

/*


spiFlags consists of the least significant 2 bits.

. .
1  0
m  m
. .

mm defines the SPI mode.

. .
Mode POL PHA
 0    0   0
 1    0   1
 2    1   0
 3    1   1
. .


*/

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

int device = 0;  // SPI device
int channel = 0; // SPI channel (0 = SPIX_CE0, 1 = SPIX_CE1)
int speed = 50000;   // SPI bps
//int flags = SPI_MODE0;   // SPI flags
int flags = SPI_MODE0;   // SPI flags
int spih = -1;    // SPI handle

bool spi_open(uint8_t spi_num, uint8_t spi_cs_num)
{
	device = spi_num;
	channel = spi_cs_num;
	
	spih = lgSpiOpen(device, channel, speed, flags);
	if(spih < 0)
	{
		return false;
	}

	return true;
}

void spi_close()
{
	if(spih >= 0)
	{
		lgSpiClose(spih);
		spih = -1;
	}
}

uint8_t spi_transfer(uint8_t val)
{
	char buf[1];

	buf[0] = val;

	lgSpiXfer(spih, buf, buf, 1);

	return buf[0];
}


/*******************************************************************/

int main()
{
	printf("____Start____\n");


	printf("spi.state: open\n");
	if(!spi_open(0, 0))
	{
		printf("spi.err: open failed\n");
		return -1;
	}

	printf("spi.state: opened\n");

	for(int i = 0; i < 5; i++)
	{

		// transfer a byte
		uint8_t val_tx = i;
		uint8_t val_rx = spi_transfer(val_tx);
		val_rx = spi_transfer(val_tx);

		printf("spi.transfer: tx=%02X, rx=%02X\n", val_tx, val_rx);

		delay(500);

	}

	printf("spi.state: close\n");
	spi_close();


	printf("____End____\n");

	return 0;
}

#endif // ENABLE_MAIN_BASIC_SPI_REG_WRITE_READ