#include "LcdMenu.h"

/**************************/
/*      LcdMenuEntry      */
/**************************/

LcdMenuEntry::LcdMenuEntry(const char id, const char* text, LcdMenuHandler* handler) 
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

LcdMenuHandler* LcdMenu::procKeyPress(const char id) {
	LcdMenuEntry* i = getCurrentTop();
	
//#if DBG
//	Serial.print("LOOKING FOR: "); Serial.println(id);
//#endif
	
	while ( i != NULL ) {
		if (i->getId() == id) {
//#if DBG
//			Serial.print("FOUND: "); Serial.println(i->getId());
//#endif
			if ( i->getHandler() != NULL ) {
//#if DBG
//				Serial.println("DELEGATE TO HANDLER");
//#endif
				//Fire off the handler for this menu item
				return i->getHandler();
			}
			else if ( i->getChild() != NULL ){
//#if DBG
//				Serial.print("NAVIGATE TO CHILD: "); Serial.println(i->getChild()->getId());
//#endif
				//Navigate to sub menu
				current = i->getChild();
				this->display();
				return NULL;				
			}
			else {
//#if DBG
//				Serial.println("NO HANDLER OR CHILD");
//#endif
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

void LcdMenuEntry::appendSibling(LcdMenuEntry* sibling) {
	LcdMenuEntry* i = this;
	while ( i-> next != NULL )
		i = i-> next;

	i->setSiblings(i->getPrev(), sibling);
	sibling->setSiblings(i, NULL);
}

/*********************/
/*      LcdMenu      */
/*********************/

LcdMenu::LcdMenu(LiquidCrystal* lcd, const int cols, const int rows)  
	:	lcd(lcd), rows(rows), cols(cols) {
	head = NULL;
	current = NULL;
};

void LcdMenu::clear() {
	lcd->clear();
//#if DBG
//	Serial.println("CLEAR");
//#endif
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
	
//#if DBG
//	Serial.print("count == rows? "); Serial.print(count); Serial.print(" == "); Serial.println(rows);
//#endif		
	
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
//#if DBG
//		Serial.println("ADVANCE");
//#endif	
		return true;
	}
	else {
//#if DBG
//		Serial.println("CANT ADVANCE");
//#endif		
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
	
//#if DBG
//	Serial.print("count == rows? "); Serial.print(count); Serial.print(" == "); Serial.println(rows);
//#endif		
	
	current = i;
	return count > 0;
}

boolean LcdMenu::stepReverse() {
	if ( current->getPrev() != NULL ) {
		current = current->getPrev();
//#if DBG
//		Serial.println("REVERSE");
//#endif		
		return true;
	}
	else {
//#if DBG
//		Serial.println("CANT REVERSE");
//#endif		
		return false;
	}
	
}

void LcdMenu::display() {
	clear();
	LcdMenuEntry* pos = current;
	short curRow = 0;
	
	while ( curRow < rows && pos != NULL ) {
//#if DBG
//		Serial.print("DISPLAY (0,");
//		Serial.print(curRow);
//		Serial.print(") ");
//		Serial.println(pos->getDisplayText());
//#endif
		lcd->setCursor(0, curRow);		
		lcd->print(pos->getDisplayText());
		
		curRow++;
			
		pos = pos->getNext();
	}
//#if DBG
//		Serial.println("DISPLAY DONE");
//#endif
}
