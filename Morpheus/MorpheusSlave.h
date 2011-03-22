#ifndef MorpheusSlave_h
#define MorpheusSlave_h

#include "WProgram.h"
#include <Wire.h>

#define N_DATA     4
#define RX_DELAY   500

class MorpheusSlave
{
public:
    MorpheusSlave();

	char command;
	char data[N_DATA];
	
	void reset();
	boolean newCommand();
	
	void receiveSerial();
	void receiveI2C(int n);
	int getIntData();
	int getIntData(int start);
	int getIntData(int start, int end);

private:
	int _rxs;
	unsigned long _lastRX;
	boolean _exec;
		
	void endComm();
};

#endif

