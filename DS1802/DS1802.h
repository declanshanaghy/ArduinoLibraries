#ifndef DS1802_h
#define DS1802_h

#include "WProgram.h"
#include <SPI.h>

#define MOSI	11
#define MISO	12
#define SCK		13

#define DS1802_MIN 0
#define DS1802_MAX 63

#define DEBUG 1

#define DBG(a) Serial.print(a)
#define DBGF(a,b) Serial.print(a,b)
#define DBGLN(a) Serial.println(a)
#define DBGLNF(a,b) Serial.println(a,b)

class DS1802
{
public:
    DS1802(int pCS, int pMute, int fClk=SPI_CLOCK_DIV128);
	void toggleMute();
	void setValues(int v0, int v1);
	void setMute(boolean m0, boolean m1);
	
private:
    int _pCS;
	int _pMute;
	int _v0;
	int _v1;
	boolean _m0;
	boolean _m1;
	void enable();
	void disable();
	void tx();
};

#endif

