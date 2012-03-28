#ifndef LCDMENUHANDLER_H
#define LCDMENUHANDLER_H

#include <LiquidCrystal.h>

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

class LcdMenuHandler {
public:
	LcdMenuHandler(): count(0) {};
	void takeControl(LiquidCrystal* lcd) { this->lcd = lcd; count=0; };
	void relinquishControl() { this->lcd != NULL; };
	boolean wantsControl() { return this->lcd != NULL; };
	
	boolean procKeyPress(int k, char c);
	void dispayCancellation(); 
	void dispayConfirmation(); 
;
	
private:
	LiquidCrystal* lcd;
	int count;
};

#endif //LCDMENUHANDLER_H

