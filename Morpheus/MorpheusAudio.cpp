#include "MorpheusAudio.h"

MorpheusAudio::MorpheusAudio(int addr)
{
	_addr = addr;
}

void MorpheusAudio::stop() {
	Wire.beginTransmission(_addr);
	Wire.send((short)'s');
	Wire.endTransmission();
}

void MorpheusAudio::playRandom() {
	Wire.beginTransmission(_addr);
	Wire.send((short)'r');
	Wire.endTransmission();
}

