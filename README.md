# Raspberry Pi Arduino for PlatformIO Native
Arduino Style Firmware/Library based on joan2937/lg written for PlatformIO Native


## Features

* Arduino style digital Functions (pinMode, digitalWrite, digitalRead)
* Arduino TwoWire (100% conform to meta standard)
    - Enable I2C before use
* Arduino SPI (99% conform to meta standart, Hardware and Software Chip Sleect)
    - Enable I2C before use
    - when Hardware CS Pins are used, SPI.transfer controlls CS. This is different from the Arduino behaviour. To get 100% the expected behaviour, use Software Chip Selects
* EEPROM Emulation



## Download & Install

### Prerequisites

In order to compile and use the project, a working PlatformIO installation in Visual Studio Code is needed. Furthermore the lgpio library must be installed. This can be done with for example (see https://github.com/joan2937/lg):

```
wget https://github.com/joan2937/lg/archive/master.zip
unzip master.zip
cd lg-master
make
sudo make install

```

## Use

Start with exploring the different Example Code Segments. They can be switched through by uncommenting defines in main.h.

If you are familiar with code you can delete the other mains and use main.cpp as a blank sketch.

use the native_linux_debug build configuration to enable debug prints. 
To disable debug prints switch to native_linux_release config