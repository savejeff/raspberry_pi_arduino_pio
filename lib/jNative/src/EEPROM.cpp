#include <Arduino.h>
#include "EEPROM.h"


#ifdef ENABLE_ARDUINO_DEBUG
#define LogX printf
#else
#define LogX(...)
#endif


#include <filesystem>
namespace fs = std::filesystem;

#include <fstream>	// std::fstream
static std::fstream file;


#define path "mem.bin"

EEPROMClass::EEPROMClass(void)
{

}

bool EEPROMClass::begin() {

	for(int i = 0; i < length(); i++)
		_data[i] = 0xFF;

	if(file.is_open())
		file.close();

	// create mem file if not exists
	if(!fs::exists(path))
	{
		LogX("eeprom.state: creating a new memory file\n");

		//file.open(path, (std::ios::in | std::ios::out | std::ios::binary));
		//file.open(path, (std::ios::in | std::ios::out | std::ios::binary | std::fstream::app));
		file.open(path, (std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc));

		//printf(">>> IS_OPEN: %d\n", file.is_open());

		//char c = 0xFF;
		char c = 'X';
		for(int i = 0; i < _size; i++)
			file.write(&c, 1);
		
		file.flush();
		file.close();

		
		//printf(">>> EXISTS: %d\n", fs::exists(path));
	}

	file.open(path, (std::ios::out | std::ios::in  | std::ios::binary));

	if(!file.is_open())
	{
		LogX("eeprom.err: open of memory file failed\n");
		return false;
	}
	
	// go to start of file
	file.seekg(0);
	file.seekp(0);

	// load from file
	file.read((char*) _data, _size);
	
	return true;
}

bool EEPROMClass::end() {
	
	if(file.is_open())
		file.close();

	return true;
}

uint8_t EEPROMClass::read(int const address) {
	if (address < 0 || (size_t)address >= _size) {
		return 0;
	}
	
	return _data[address];
}

void EEPROMClass::write(int const address, uint8_t const value) {
	if (address < 0 || (size_t)address >= _size) {
		return;
	}
	if (!_data) {
		return;
	}

	_data[address] = value;
}

bool EEPROMClass::commit() {
	if (!_size) {
		return false;
	}

	if(file.is_open()) {

		// go to start of file
		file.seekg(0);
		file.seekp(0);

		// override file content with memory in ram
		file.write((char*) _data, _size);	

		return true;
	}
	
	return false;
}


EEPROMClass EEPROM;
