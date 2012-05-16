#include "LcdMenuHandler.h"

boolean LcdMenuHandler::procKeyPress(int k, char c) { 
	this->val = !this->val;
	return false; 
};

void LcdMenuHandler::displayConfirmation() {
	lcd->setCursor(5, 0);
	lcd->print("=-==-=");      
	lcd->setCursor(3, 1);
	lcd->print("=-= OK =-=");      
}

void LcdMenuHandler::displayCancellation() {
	lcd->setCursor(5, 0);
	lcd->print("=-==-=");      
	lcd->setCursor(3, 1);
	lcd->print("=-= XX =-=");      
}
