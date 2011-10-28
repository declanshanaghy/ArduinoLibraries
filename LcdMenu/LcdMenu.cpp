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
#ifdef DEBUG
	Serial.println("CLEAR");
#endif
}

boolean LcdMenu::page() {
	short count = 0;
	while ( count < _rows ) {
		count++;
		if (!step())
			break;
	}
#ifdef DEBUG
	Serial.print("count == _rows? "); Serial.print(count); Serial.print(" == "); Serial.println(_rows);
#endif		
	return count == _rows;
}

boolean LcdMenu::step() {
	if ( _current->_next != NULL ) {
		_current = _current->_next;
#ifdef DEBUG
		Serial.println("ADVANCE");
#endif		
		return true;
	}
	else {
#ifdef DEBUG
		Serial.println("CANT ADVANCE");
#endif		
		return false;
	}
	
}

boolean LcdMenu::pageReverse() {
	short count = 0;
	while ( count < _rows ) {
		count++;
		if (!stepReverse())
			break;
	}
#ifdef DEBUG
	Serial.print("count == _rows"); Serial.print(count); Serial.print(" == "); Serial.println(_rows);
#endif		
	return count == _rows;
}

boolean LcdMenu::stepReverse() {
	if ( _current->_prev != NULL ) {
		_current = _current->_prev;
#ifdef DEBUG
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

void LcdMenu::display() {
	clear();
	LcdMenuEntry* pos = _current;
	short curRow = 0;
	
	while ( curRow < _rows && pos != NULL ) {
#ifdef DEBUG
		Serial.print("DISPLAY "); Serial.println(pos->displayText);
#endif
		_lcd.setCursor(0, curRow);
		_lcd.print(pos->displayText);
		curRow++;
			
		pos = pos->_next;
	}
#ifdef DEBUG
		Serial.println("DISPLAY DONE");
#endif
}
