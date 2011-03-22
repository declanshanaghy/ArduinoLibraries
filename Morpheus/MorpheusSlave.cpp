#include "MorpheusSlave.h"

MorpheusSlave::MorpheusSlave()
{
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
	_rxs = 0;
	_lastRX = -1;
	_exec = false;
	command = 0;
    for ( int i=0; i<N_DATA; i++)
		data[i] = 0;
	
}

int MorpheusSlave::getIntData() {
	return getIntData(0, N_DATA);
}

int MorpheusSlave::getIntData(int start) {
	return getIntData(start, N_DATA);
}

int MorpheusSlave::getIntData(int start, int end) {
	int v = 0;
	char ch;
		
	for ( int i=start; i<N_DATA && i < end; i++ ) {
		ch = data[i];  
		switch(data[i]) {
			case '0'...'9':
				v = v * 10 + ch - '0';
				break;
			case 0:
				break;
			default:
				Serial.print("getIntData: unahndled - ");
				Serial.println(ch);
				break;
		}
	}
	return v;
}

void MorpheusSlave::endComm() {
	_rxs = 0;
	_lastRX = -1;
	_exec = true;
	Serial.flush();
    
	Serial.print("command: ");
	Serial.print(command);
	Serial.print(" ");
	for ( int i=0; i<N_DATA; i++) {
		Serial.print(data[i]);
	}
	Serial.println();
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
						Serial.print("SER receiveEvent: ");
						command = b;
						break;
					default:
						data[_rxs-1] = b;
						break;
				}
			}
			_rxs++;
		}
		
		if ( _rxs > N_DATA ) {
			endComm();
		}
	}
	
	if ( _lastRX != -1 && millis() - _lastRX > RX_DELAY ) {
		endComm();
	}
}

void MorpheusSlave::receiveI2C(int n) {
	Serial.print("I2C receiveEvent: ");
	Serial.println(n);
	
	int i = 0;
	Serial.print("I2C: ");
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

