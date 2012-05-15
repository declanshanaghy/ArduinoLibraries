#ifndef LCDMENUHANDLER_H
#define LCDMENUHANDLER_H

#include <Arduino.h>
#include <LiquidCrystal.h>


class LcdMenuHandler {
public:
	LcdMenuHandler(int ident) { this->ident = ident; this->val = 0; };
	virtual ~LcdMenuHandler() {};
	void takeControl(LiquidCrystal* lcd) { this->lcd = lcd; this->active = true; };
	void relinquishControl() { this->lcd = NULL; this->active = false; };
	boolean wantsControl() { return this->active; };
	
	virtual boolean procKeyPress(int k, char c);
	virtual void dispayCancellation(); 
	virtual void dispayConfirmation(); 

	int getIdent() { return ident; };
	void setValue(short value) { val = value; };
	short getValue() { return val; };

protected:
	short val;
	boolean active;
	LiquidCrystal* lcd;
	
private:
	int ident;
};

#endif //LCDMENUHANDLER_H

