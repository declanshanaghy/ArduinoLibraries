#ifndef Morse_h
#define Morse_h

#include "WProgram.h"
#include <SPI.h>

#define MOSI	11
#define MISO	12
#define SCK		13

class MCP4161
{
public:
    MCP4161(int csPin);
	int initTCON();
	int readTCON();
	int readStatus();
	int increment();
	int decrement();
	int setTap(int value);
	
private:
    int _cs;
	void enable();
	void disable();
};

#endif

