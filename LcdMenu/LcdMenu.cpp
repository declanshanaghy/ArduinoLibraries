#include "LcdMenu.h"

LcdMenuEntry::LcdMenuEntry(const char id, const char* text, HANDLER handler) 
	: id(id), text(text), handler(handler) {
	displayText = (char*)malloc(sizeof(char) * strlen(text) + 4);
	sprintf(displayText, "%c %s", id, text);
}

LcdMenuEntry::~LcdMenuEntry() {
	free(displayText);
}

LcdMenu::~LcdMenu() {
	head = current = NULL;
}

void LcdMenu::setHead(LcdMenuEntry* main) {
	current = head = main;
}

LcdMenuEntry* LcdMenu::getCurrentTop() {
	/*
	 Traverse the current sub menu until there 
	 are no previous sibling. and return the first entry
	 */
	LcdMenuEntry* i = current;
	while ( i->getPrev() != NULL ) {
		i = i->getPrev();
	}
	return i;
}

boolean LcdMenu::levelUp() {
	LcdMenuEntry* top = getCurrentTop();
	if ( top->getParent() != NULL ) {
		current = top->getParent();
		return true;
	}
	return false;
}

LcdMenuEntry* LcdMenu::selectEntry(const char id) {
	LcdMenuEntry* i = getCurrentTop();
	
#ifdef DEBUG
	Serial.print("LOOKING FOR: "); Serial.println(id);
#endif
	
	while ( i != NULL ) {
		if (i->getId() == id) {
#ifdef DEBUG
			Serial.print("FOUND: "); Serial.println(i->getId());
#endif
			if ( i->getHandler() != NULL ) {
#ifdef DEBUG
				Serial.println("CALL HANDLER");
#endif
				//Fire off the handler for this menu item
				(*i->getHandler())();
				return i;				
			}
			else if ( i->getChild() != NULL ){
#ifdef DEBUG
				Serial.print("NAVIGATE TO CHILD: "); Serial.println(i->getChild()->getId());
#endif
				//Navigate to sub menu
				current = i->getChild();
				return i;				
			}
			else {
#ifdef DEBUG
				Serial.println("NO HANDLER OR CHILD");
#endif
				//Invalid menu entry - no handler or child
				return NULL;
			}
		}
		else {
			i = i->getNext();
		}
	}
	return NULL;	
}

void LcdMenu::clear() {
	lcd.clear();
#ifdef DEBUG
	Serial.println("CLEAR");
#endif
}

boolean LcdMenu::page() {
	LcdMenuEntry* i = current;
	short count = 0;
	while ( count < rows ) {
		if (i->getNext() != NULL) {
			i = i->getNext();
			count++;
		}
		else
			break;
	}
	
#ifdef DEBUG
	Serial.print("count == rows? "); Serial.print(count); Serial.print(" == "); Serial.println(rows);
#endif		
	
	if ( count == 0 ) {
		return false;
	}
	if ( count == rows ) {
		current = i;
		return true;
	}
	else {
		current = i->getPrev();
		return true;
	}
}

boolean LcdMenu::step() {
	if ( current->getNext() != NULL && current->getNext()->getNext() != NULL ) {
		current = current->getNext();
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
	LcdMenuEntry* i = current;
	short count = 0;
	while ( count < rows ) {
		if (i->getPrev() != NULL) {
			i = i->getPrev();
			count++;
		}
		else
			break;
	}
	
#ifdef DEBUG
	Serial.print("count == rows? "); Serial.print(count); Serial.print(" == "); Serial.println(rows);
#endif		
	
	current = i;
	return count > 0;
}

boolean LcdMenu::stepReverse() {
	if ( current->getPrev() != NULL ) {
		current = current->getPrev();
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
	LcdMenuEntry* pos = current;
	short curRow = 0;
	
	while ( curRow < rows && pos != NULL ) {
#ifdef DEBUG
		Serial.print("DISPLAY "); Serial.println(pos->getDisplayText());
#endif
		lcd.setCursor(0, curRow);
		lcd.print(pos->getDisplayText());
		curRow++;
			
		pos = pos->getNext();
	}
#ifdef DEBUG
		Serial.println("DISPLAY DONE");
#endif
}
