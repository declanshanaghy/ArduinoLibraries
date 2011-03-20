#include "MorpheusSlave.h"

MorpheusSlave::MorpheusSlave(int addr)
{
	_addr = addr;

	reset();
	
	// if analog input pin 0 is unconnected, random analog
	// noise will cause the call to randomSeed() to generate
	// different seed numbers each time the sketch runs.
	// randomSeed() will then shuffle the random function.
	randomSeed(analogRead(0));

	Wire.begin(addr); // join i2c bus as a slave

}

boolean MorpheusSlave::newCommand() {
	return exec;
}

void MorpheusSlave::reset() {
	rxs = 0;
	lastRX = -1;
	exec = false;
	command = 0;
    for ( int i=0; i<N_DATA; i++)
		data[i] = 0;
	
}

void MorpheusSlave::endComm() {
	rxs = 0;
	lastRX = -1;
	exec = true;
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
			if ( rxs > N_DATA ) {
				endComm();
				break;
			}
			
			lastRX = millis();
			b = Serial.read();
			if ( b == '\n' ) {
				endComm();
				break;
			}
			else {
				switch ( rxs ) {
					case 0:
						command = b;
						break;
					default:
						data[rxs-1] = b;
						break;
				}
			}
			rxs++;
		}
		
		if ( rxs > N_DATA ) {
			endComm();
		}
	}
	
	if ( lastRX != -1 && millis() - lastRX > RX_DELAY ) {
		endComm();
	}
}

void MorpheusSlave::receiveEvent(int n) {
	Serial.print("receiveEvent: ");
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
				Serial.print(data[i-1]);
				break;
		}
		i++;
	}
}

