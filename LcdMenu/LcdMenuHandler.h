#ifndef LCDMENUHANDLER_H
#define LCDMENUHANDLER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define TYPE_SHORT 0
#define TYPE_INT 1
#define TYPE_LONG 2

class LcdMenuHandler {
public:
	LcdMenuHandler(int ident) { this->ident = ident; this->val = 0; this->state=0; };
	virtual ~LcdMenuHandler() {};
	void takeControl(LiquidCrystal* lcd) { this->lcd = lcd; this->active = true; };
	void relinquishControl() { this->lcd = NULL; this->active = false; };
	boolean wantsControl() { return this->active; };
	
	virtual boolean procKeyPress(int k, char c);
	virtual void displayStart() {}; 
	virtual void displayCancellation(); 
	virtual void displayConfirmation(); 

	int getIdent() { return ident; };
	virtual short getValueType() { return TYPE_SHORT; };
	
	void setValue(long value) { val = value; };
	long getValue() { return val; };

protected:
	short state;
	long val;
	boolean active;
	LiquidCrystal* lcd;
	
private:
	int ident;
};

#endif //LCDMENUHANDLER_H

