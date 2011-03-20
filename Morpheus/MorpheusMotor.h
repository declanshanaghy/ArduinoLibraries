#ifndef MorpheusMotor_h
#define MorpheusMotor_h

#include "WProgram.h"
#include <Wire.h>

class MorpheusMotor
{
public:
    MorpheusMotor(int addr);
	
private:
    int _addr;
};

#endif

