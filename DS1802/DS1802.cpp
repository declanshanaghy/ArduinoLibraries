#include "DS1802.h"

DS1802::DS1802(int pCS, int pMute, int fClk)
{
	_pCS = pCS;
	pinMode(_pMute, OUTPUT);
	
	pMute = pMute;
	pinMode(_pMute, OUTPUT);
	mute();
	
	disable();

	SPI.begin();
	SPI.setBitOrder(LSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(fClk);
	
	_v0 = DS1802_MIN;
	_v1 = DS1802_MIN;
	setMute(true, true);
}

void DS1802::mute() {
	digitalWrite(_pMute, HIGH);
}

void DS1802::unmute() {
	digitalWrite(_pMute, LOW);
}

void DS1802::setMute(boolean m0, boolean m1) {
	_m0 = m0 ? 0x7F : 0x3F;
	_m1 = m1 ? 0x7F : 0x3F;
	tx();
}

void DS1802::setValues(int v0, int v1) {
	if ( v0 < DS1802_MIN ) v0 = DS1802_MIN;
	if ( v0 > DS1802_MAX ) v0 = DS1802_MAX;
	
	if ( v1 < DS1802_MIN ) v1 = DS1802_MIN;
	if ( v1 > DS1802_MAX ) v1 = DS1802_MAX;
	
	_v0 = v0;
	_v1 = v1;
	
	tx();
}

void DS1802::enable() {
	digitalWrite(_pCS, HIGH);
}

void DS1802::disable() {
	digitalWrite(_pCS, LOW);
}

void DS1802::tx() {
	int vc0 = (_m0 & _v0);
	int vc1 = (_m1 & _v1);
			   
	enable();
	SPI.transfer(vc0);
	SPI.transfer(vc1);
	disable();
	
	DBG("DS1802::setValues: ");
	DBGLN(vc0, BIN);
	DBG(" ");
	DBGLN(vc1, BIN);
}
			   
