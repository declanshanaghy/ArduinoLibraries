#include "AnalogKeypad.h"

AnalogKeypad::AnalogKeypad(int pin, int rLadder, int rPull, int vcc, int adcMax)
{
	_pin = pin;
	_rLadder = rLadder;
	_rPull = rPull;
	_vcc = vcc;
	_adcMax = adcMax;
}

void AnalogKeypad::init() {
	float v, vK;
	float stv = (float)_adcMax / _vcc;
	
	//Calculate all the voltage divider values for each key and map into an array
	for ( int i=0; i<12; i++ ) {
		vK = _rLadder * (i+1);
		v = (vK / (_rPull + vK)) * _vcc;
		_vals[i] = v * stv;
		Serial.print("vals["); Serial.print(i); Serial.print("] = "); Serial.println(_vals[i]);
	}
	
	//Calc th emin gap between values as a threshold to use when reading keys
	int g;
	_minGap = 32767;
	for ( int i=0; i<11; i++ ) {
		g = (_vals[i+1] - _vals[i]) / 2;
		if ( g < _minGap )
			_minGap = g;
	}
	Serial.print("_minGap="); Serial.println(_minGap);
}

//TODO: Debounce this.
int AnalogKeypad::readKey()
{
	int v = analogRead(_pin);
//	Serial.print("keyV="); Serial.println(v);
	
	//No key pressed
	if ( v >= _vals[11] + _minGap )
		return -1;
	
	//Cycle thru all key values from highest to lowest and find the closest mapping
	for ( int i=11; i>=0; i-- ) {
		if ( v >= _vals[i] - _minGap )
			return i;
	}
}