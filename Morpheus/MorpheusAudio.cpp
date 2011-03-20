#include "MorpheusAudio.h"

MorpheusAudio::MorpheusAudio(int addr)
{
	_addr = addr;
}

void MorpheusAudio::stop() {
	Wire.beginTransmission(_addr);
	Wire.send('S');
	Wire.endTransmission();
}

void MorpheusAudio::playRandom() {
	Wire.beginTransmission(_addr);
	Wire.send('R');
	Wire.endTransmission();
}

