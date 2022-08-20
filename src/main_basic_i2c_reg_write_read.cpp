#include "main.h"
#ifdef ENABLE_MAIN_BASIC_I2C_REG_WRITE_READ

#include "Arduino.h"



#include <lgpio.h>

/*******************************************************************/

// BMS280 Register
#define BMP280_I2C_ADDR			0x77				// The BMP280 I2C address
#define BMP280_I2C_ALT_ADDR		0x76				// The BMP280 I2C alternate address

#define REG_BMP280_DEVICE_ID	0xD0				// Device ID register sub-address
#define BMP280_DEVICE_ID		0x58				// The BMP280 device ID


// FRAM Register
#define FRAM_I2C_ADDR			0x50 //0xA0
#define FRAM_I2C_ADDR_2			0x51 //0xA2


#define DEVICE_I2C_ADDR FRAM_I2C_ADDR
#define REG_I2C_TEST_RW 0x41

//#define DEVICE_I2C_ADDR BMP280_I2C_ADDR
//#define REG_I2C_TEST_R REG_BMP280_DEVICE_ID

/*******************************************************************/


int bus = 1;       // I2C bus
int device = DEVICE_I2C_ADDR;    // I2C device address
int flags = 0;     // I2C flags
int i2ch = -1;      // I2C handle

bool i2c_open(uint8_t addr)
{
	device = addr;
	
	i2ch = lgI2cOpen(bus, device, flags);
	if(i2ch < 0)
	{
		return false;
	}

	return true;
}

void i2c_close()
{
	if(i2ch >= 0)
	{
		lgI2cClose(i2ch);
		i2ch = -1;
	}
}

int i2c_write(uint8_t reg, uint8_t val)
{
	char buf[2];

	buf[0] = reg;
	buf[1] = val;

	lgI2cWriteDevice(i2ch, buf, 2);

	return 0;
}

uint8_t i2c_read(uint8_t reg)
{

	char buf[8];

	buf[0] = reg;

	lgI2cWriteDevice(i2ch, buf, 1);  // register

	lgI2cReadDevice(i2ch, buf, 1); // read value

	return buf[0];
}

/*******************************************************************/

int main()
{
	printf("____Start____\n");


	printf("i2c.state: open\n");
	if(!i2c_open(DEVICE_I2C_ADDR))
	{
		printf("i2c.err: open failed\n");
		return -1;
	}

	printf("i2c.state: opened\n");

	// write to register
	uint8_t val_w = 0x1A;
	printf("i2c.write: val=%02X\n", val_w);
	i2c_write(REG_I2C_TEST_RW, val_w);


	// read from register
	uint8_t val_r = i2c_read(REG_I2C_TEST_RW);
	printf("i2c.read: val=%02X\n", val_r);
	

	printf("i2c.state: close\n");
	i2c_close();


	printf("____End____\n");

	return 0;
}

#endif // ENABLE_MAIN_BASIC_I2C_REG_WRITE_READ