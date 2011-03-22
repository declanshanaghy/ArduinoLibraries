#ifndef MorpheusMotor_h
#define MorpheusMotor_h

#include "WProgram.h"
#include <Wire.h>

class MorpheusMotor
{
public:
    MorpheusMotor(int addr);
	void setDCMotorParams(short n, short dir, int spd);
	void setServoParams(short n, short angle);
	void testDCMotors();
	void testServos();
	
private:
    int _addr;
	char _num[3];
};

#endif

