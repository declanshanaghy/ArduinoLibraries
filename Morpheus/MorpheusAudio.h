#ifndef MorpheusAudio_h
#define MorpheusAudio_h

#include "WProgram.h"
#include <Wire.h>

class MorpheusAudio
{
public:
    MorpheusAudio(int addr);
	void stop();
	void playRandom();
	
private:
    int _addr;
};

#endif

