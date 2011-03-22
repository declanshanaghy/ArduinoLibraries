#include "MorpheusMotor.h"

MorpheusMotor::MorpheusMotor(int addr)
{
	_addr = addr;
}

void MorpheusMotor::setServoParams(short n, short angle) {
	if ( n < 1 || n > 4 ) {
		Serial.print("Invalid servo number: ");
		Serial.println(n);		
		return;
	}
	if ( angle < 0 || angle > 180 ) {
		Serial.print("Invalid angle: ");
		Serial.println(angle);		
		return;
	}
	
	itoa(angle, _num, 10);
	Wire.beginTransmission(_addr);
	Wire.send((short)'e' + n-1);
	Wire.send((short)_num[0]);
	Wire.send((short)_num[1]);
	Wire.send((short)_num[2]);
	Wire.endTransmission();
	delay(100);
}

void MorpheusMotor::setDCMotorParams(short n, short dir, int spd) {
	if ( n < 1 || n > 4 ) {
		Serial.print("Invalid motor number: ");
		Serial.println(n);		
		return;
	}
	if ( dir < 1 || dir > 4 ) {
		Serial.print("Invalid direction: ");
		Serial.println(dir);		
		return;
	}
	if ( spd < 0 || spd > 255 ) {
		Serial.print("Invalid speed: ");
		Serial.println(spd);		
		return;
	}

	itoa(spd, _num, 10);
	Wire.beginTransmission(_addr);
	Wire.send((short)'a' + n-1);
	Wire.send((short)'1' + dir-1);
	Wire.send((short)_num[0]);
	Wire.send((short)_num[1]);
	Wire.send((short)_num[2]);
	Wire.endTransmission();
	delay(100);
}
	
void MorpheusMotor::testDCMotors() {
	Wire.beginTransmission(_addr);
	Wire.send((short)'t');
	Wire.send((short)'d');
	Wire.endTransmission();
}

void MorpheusMotor::testServos() {
	Wire.beginTransmission(_addr);
	Wire.send((short)'t');
	Wire.send((short)'s');
	Wire.endTransmission();
}
