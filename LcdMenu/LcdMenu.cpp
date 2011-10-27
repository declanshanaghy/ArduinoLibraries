#include "LcdMenu.h"

LcdMenuEntry::LcdMenuEntry(const short id, const char* text) 
	: _id(id), _text(text) {
	displayText = (char*)malloc(sizeof(char) * strlen(_text) + 4);
	sprintf(displayText, "%d %s", _id, _text);
}

LcdMenuEntry::~LcdMenuEntry() {
	free(displayText);
}

LcdMenu::~LcdMenu() {
	_head = _current = NULL;
}

void LcdMenu::setHead(LcdMenuEntry* main) {
	_current = _head = main;
}

void LcdMenu::clear() {
	_lcd.clear();
	_lcd.setCursor(0, 0);
	_curRow = 0;
#if DEBUG
	Serial.println("CLEAR");
#endif
}

boolean LcdMenu::advance() {
	if ( _current->_next != NULL ) {
		_current = _current->_next;
		_curRow++;
		_lcd.setCursor(0, _curRow);
#if DEBUG
		Serial.println("ADVANCE");
#endif		
		return true;
	}
	else {
#if DEBUG
		Serial.println("CANT ADVANCE");
#endif		
		return false;
	}
	
}

boolean LcdMenu::reverse() {
	if ( _current->_prev != NULL ) {
		_current = _current->_prev;
		_curRow--;
		_lcd.setCursor(0, _curRow);
#if DEBUG
		Serial.println("REVERSE");
#endif		
		return true;
	}
	else {
#if DEBUG
		Serial.println("CANT REVERSE");
#endif		
		return false;
	}
	
}

void LcdMenu::displayCurrent() {
#if DEBUG
	Serial.print("DISPLAY "); Serial.println(_current->displayText);
#endif
	_lcd.print(_current->displayText);
}

void LcdMenu::display() {
	clear();
	
	if ( _current != NULL ) {
		do {
			displayCurrent();
		}
		while ( _curRow < _rows-1 && advance() );
#if DEBUG
		Serial.println("DISPLAY DONE");
#endif
	}
}
