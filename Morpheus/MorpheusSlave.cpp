#include "MorpheusSlave.h"

MorpheusSlave::MorpheusSlave(int nData)
{
	_nData = nData;
	reset();
	
	// if analog input pin 0 is unconnected, random analog
	// noise will cause the call to randomSeed() to generate
	// different seed numbers each time the sketch runs.
	// randomSeed() will then shuffle the random function.
	randomSeed(analogRead(0));
}

boolean MorpheusSlave::newCommand() {
	return _exec;
}

void MorpheusSlave::reset() {
#if DBG
	Serial.print("reset");
#endif
	_rxs = 0;
	_lastRX = -1;
	_exec = false;
	command = NULL;
    for ( int i=0; i<N_DATA; i++)
		data[i] = NULL;	
}

uint8_t MorpheusSlave::getData(int pos) {
	return data[pos];
}

char MorpheusSlave::getChar(int pos) {
	return data[pos];
}

void MorpheusSlave::endComm() {
	_rxs = 0;
	_lastRX = -1;
	_exec = true;
	//Serial.flush();
    
#if DBG
	Serial.print("command: ");
	Serial.print(command);
	Serial.print(" ");
	for ( int i=0; i < N_DATA && data[i] != NULL; i++) {
		Serial.print(data[i], DEC);
		Serial.print(',');
	}
	Serial.println();
#endif
}

void MorpheusSlave::receiveSerial() {
	if ( Serial.available() )  {
		byte b;
		while ( Serial.available() > 0 ) {
			if ( _rxs > N_DATA ) {
				endComm();
				break;
			}
			
			_lastRX = millis();
			b = Serial.read();
			if ( b == '\n' ) {
				endComm();
				break;
			}
			else {
				switch ( _rxs ) {
					case 0:
#if DBG
						Serial.print("SER receiveEvent: ");
#endif
						command = b;
						break;
					default:
						data[_rxs-1] = b;
						break;
				}
			}
			_rxs++;
			if ( _rxs == _nData ) {
				endComm();
				break;
			}
		}
		
		if ( _rxs > N_DATA ) {
			endComm();
		}
	}
	
	if ( _lastRX != -1 && millis() - _lastRX > RX_TIMEOUT ) {
		endComm();
	}
}

void MorpheusSlave::receiveI2C(int n) {
#if DBG
	Serial.print("I2C receiveEvent: ");
	Serial.println(n);
	Serial.print("I2C: ");
#endif
	
	int i = 0;
	while ( Wire.available() > 0 ){
		if ( i > N_DATA ) {
			break;
		}
		switch ( i ) {
			case 0:
				command = Wire.receive();
				break;
			default:
				data[i-1] = Wire.receive();
				break;
		}
		i++;
	}
	
	endComm();
}

