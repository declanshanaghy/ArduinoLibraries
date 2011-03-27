#ifndef MorpheusSlave_h
#define MorpheusSlave_h

#include "WProgram.h"
#include <Wire.h>

#define N_DATA		4
#define RX_TIMEOUT	100

class MorpheusSlave
{
public:
    MorpheusSlave(int nData);

	char command;
	uint8_t data[N_DATA];
	
	void reset();
	boolean newCommand();
	
	void receiveSerial();
	void receiveI2C(int n);
	uint8_t getData(int pos);
	char getChar(int pos);

private:
	int _rxs;
	int _nData;
	unsigned long _lastRX;
	boolean _exec;
		
	void endComm();
};

#endif

