#include "LcdMenuHandler.h"

boolean LcdMenuHandler::procKeyPress(int k, char c) { 
	lcd->clear();
	lcd->setCursor(0, 0);		
	lcd->print("HELLO "); 
	lcd->setCursor(7, 0);		
	lcd->print(count); 
	
	return count++ % 2 == 0; 
};

void LcdMenuHandler::dispayConfirmation() {
	lcd->setCursor(5, 0);
	lcd->print("=-==-=");      
	lcd->setCursor(3, 1);
	lcd->print("=-= OK =-=");      
}

void LcdMenuHandler::dispayCancellation() {
	lcd->setCursor(5, 0);
	lcd->print("=-==-=");      
	lcd->setCursor(3, 1);
	lcd->print("=-= XX =-=");      
}
