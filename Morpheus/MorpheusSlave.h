#ifndef MorpheusSlave_h
#define MorpheusSlave_h

#include "WProgram.h"
#include <Wire.h>

#define N_DATA     2
#define RX_DELAY   500

class MorpheusSlave
{
public:
    MorpheusSlave(int addr);

	char command;
	char data[N_DATA];
	
	void receiveSerial();
	void reset();
	boolean newCommand();
	void receiveEvent(int n);

private:
    int _addr;
	int rxs;
	unsigned long lastRX;
	boolean exec;
		
	void endComm();
};

#endif

