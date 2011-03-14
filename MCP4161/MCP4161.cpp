#include "MCP4161.h"

MCP4161::MCP4161(int csPin)
{
	_cs = csPin;
	pinMode(_cs, OUTPUT);
	disable();

	//Increase the frequency when external pull ups are used
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV128);
}

void MCP4161::enable() {
	// take the SS pin low to select the chip:
	digitalWrite(_cs, LOW);
}

void MCP4161::disable() {
	// take the SS pin high to de-select the chip:
	digitalWrite(_cs, HIGH);
}

int MCP4161::increment() {
	enable();
	
	//  send in the address and value via SPI:
	byte ret1 = SPI.transfer(0x04);

	disable();
	return ret1;
}

int MCP4161::decrement() {
	enable();
	
	//  send in the address and value via SPI:
	byte ret1 = SPI.transfer(0x08);
	
	disable();
	return ret1;
}

int MCP4161::readTCON() {
	enable();
	
	//  send in the address and value via SPI:
	byte ret1 = SPI.transfer(0x4C);
	byte ret2 = SPI.transfer(0x00);
	
	disable();
	return ret1;
}

int MCP4161::initTCON() {
	enable();
	
	//  send in the address and value via SPI:
	byte ret1 = SPI.transfer(0x41);
	byte ret2 = SPI.transfer(0x0F);
	
	disable();
	return ret1;
}

int MCP4161::readStatus() {
	enable();
	
	//  send in the address and value via SPI:
	byte ret1 = SPI.transfer(0x5C);
	byte ret2 = SPI.transfer(0x00);
	
	disable();
	return ret1;
}

int MCP4161::setTap(int value) {
	enable();

	//  send in the address and value via SPI:
	byte ret1 = SPI.transfer(0x0C);
	byte ret2 = SPI.transfer(0x00);

	disable();	
	return 0;
}
