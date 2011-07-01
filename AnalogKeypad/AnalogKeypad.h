#ifndef ANALOGKEYPAD_h
#define ANALOGKEYPAD_h

#include "WProgram.h"

#define DEBUG 1

#define KEY_NONE		-1
#define KEY_STAR		0
#define KEY_7			1
#define KEY_4			2
#define KEY_1			3
#define KEY_0			4
#define KEY_8			5
#define KEY_5			6
#define KEY_2			7
#define KEY_POUND		8
#define KEY_9			9
#define KEY_6			10
#define KEY_3			11

class AnalogKeypad
{
public:
    AnalogKeypad(int pin, int rLadder=1000, int rPull=10000, int vcc=5, int adcMax=1023);
	int readKey();
	void init();
	
private:	
	int _pin;
	int _rLadder;
	int _rPull;
	int _vcc;
	int _adcMax;
	int _minGap;
	
	int _vals[12];
};

#endif

