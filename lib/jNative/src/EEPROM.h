#pragma once

#include "Arduino.h"

#ifndef EEPROM_SIZE 
	#define EEPROM_SIZE 1024
#endif // EEPROM_SIZE

class EEPROMClass {
public:
	EEPROMClass(void);

	bool begin();
	bool end();
	
	uint8_t read(int const address);
	void write(int const address, uint8_t const val);
	
	// write eeprom data to file
	bool commit();
	

	

	template<typename T>
	T &get(int const address, T &t) {
		if (address < 0 || address + sizeof(T) > _size) {
			return t;
		}

		memcpy((uint8_t*) &t, _data + address, sizeof(T));
		return t;
	}

	template<typename T>
	const T &put(int const address, const T &t) {
		if (address < 0 || address + sizeof(T) > _size) {
			return t;
		}
		if (memcmp(_data + address, (const uint8_t*)&t, sizeof(T)) != 0) {
			memcpy(_data + address, (const uint8_t*)&t, sizeof(T));
		}

		return t;
	}

	size_t length() {
		return _size;
	}

	uint8_t& operator[](int const address) {
		return _data[address];
	}
	uint8_t const & operator[](int const address) const {
		return _data[address];
	}

protected:
	
	// inter-buffer that stores data in ram. only commit writes out to file
	uint8_t _data[EEPROM_SIZE];
	size_t _size = EEPROM_SIZE;
	
};

extern EEPROMClass EEPROM;

