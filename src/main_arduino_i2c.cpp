#include "main.h"
#ifdef ENABLE_MAIN_ARDUINO_I2C

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

#include "Wire.h"

TwoWire Wire(1);

/*******************************************************************/

void setup()
{
	printf("____Start____\n");

	printf("i2c.state: begin\n");
	Wire.begin();	
}

void loop() {

	static uint32_t loop_count = 0;
	loop_count++;

	uint8_t reg = REG_I2C_TEST_RW;
	uint8_t device_addr = DEVICE_I2C_ADDR;

	if(false) { // single write and read 

		uint8_t data = 0;
		
		// Write register
		data = loop_count;
		Wire.beginTransmission(device_addr);
		uint8_t buf[2];
		buf[0] = reg;
		buf[1] = data;
		Wire.write(buf, 2);
		//Wire.write(reg);
		//Wire.write(data);
		Wire.endTransmission();
		
		printf("i2c.w: reg=%02X, val=x%02X\n", reg, data);

		// Read register
		Wire.beginTransmission(device_addr);
		Wire.write(reg);
		Wire.endTransmission(false);
		Wire.requestFrom(device_addr, 1);
		data = Wire.read();
		Wire.endTransmission();
		
		printf("i2c.r: reg=%02X, val=x%02X\n", reg, data);

	}

	if(true) { // multi write and read 

		uint8_t data_low = loop_count;
		uint8_t data_high = loop_count + 1;
		
		// Write register
		Wire.beginTransmission(device_addr);
		//uint8_t buf[3];
		//buf[0] = reg;
		//buf[1] = data_low;
		//buf[2] = data_high;
		//Wire.write(buf, 3);
		Wire.write(reg);
		Wire.write(data_low);
		Wire.write(data_high);
		Wire.endTransmission();
		
		printf("i2c.w: reg=%02X, val=x%02X%02X\n", reg, data_low, data_high);

		// Read register
		Wire.beginTransmission(device_addr);
		Wire.write(reg);
		Wire.endTransmission(false);
		Wire.requestFrom(device_addr, 2);
		data_low = Wire.read();
		data_high = Wire.read();
		Wire.endTransmission();
		
		printf("i2c.r: reg=%02X, val=x%02X%02X\n", reg, data_low, data_high);

	}

	delay(1000);

	if(millis() > 10 * 1000)
	{
		printf("i2c.state: end\n");
		Wire.end();

		printf("___ END __");
		terminate();
	}
}

#endif // ENABLE_MAIN_ARDUINO_I2C