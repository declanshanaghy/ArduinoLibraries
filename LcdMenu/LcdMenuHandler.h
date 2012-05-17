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
	virtual short getValueType() { return TYPE_SHORT; };

	boolean isConfirmed() { return this->confirmed; };
	boolean isValid() { return this->valid; };
	int getIdent() { return ident; };
	
	void setValue(long value) { val = value; };
	long getValue() { return val; };

protected:
	// Holds internal state between keypresses
	short state;
	// Determines whether the user canceled or confirmed the action before the handler exited
	boolean confirmed;
	// Determines whether the last keypress was valid input or not
	boolean valid;
	// The value the user entered
	long val;
	// Whether the handler is currently active (receiving keypresses)
	boolean active;
	// The attached LCD to output user feedback
	LiquidCrystal* lcd;
	
private:
	// Handler identity (should be unique to this handler)
	int ident;
};

#endif //LCDMENUHANDLER_H

