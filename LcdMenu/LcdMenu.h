#ifndef LCDMENUh
#define LCDMENUh

#include <WProgram.h>
#include <LiquidCrystal.h>

#define DEBUG 1

typedef void (*HANDLER)(void);

class LcdMenuEntry {
public:
	LcdMenuEntry(const char id, const char* text, HANDLER handler);
	~LcdMenuEntry();
	
	void setChild(LcdMenuEntry* child) { this->child = child; child->parent = this; };	
	void setPrev(LcdMenuEntry* prev) { this->prev = prev; };	
	void setNext(LcdMenuEntry* next) { this->next = next; };	
	void setSiblings(LcdMenuEntry* prev, LcdMenuEntry* next) { this->prev = prev; this->next = next; };	
	
	const char getId() { return id; };
	const char* getDisplayText() { return displayText; };
	const char* getText() { return text; };
	LcdMenuEntry* getParent() { return parent; };
	LcdMenuEntry* getChild() { return child; };
	LcdMenuEntry* getPrev() { return prev; };
	LcdMenuEntry* getNext() { return next; };
	HANDLER getHandler() { return handler; };
	
private:
	const int id;
	const char* text;
	char* displayText;
	LcdMenuEntry* parent;
	LcdMenuEntry* child;
	LcdMenuEntry* prev;
	LcdMenuEntry* next;
	HANDLER handler;
};

class LcdMenu
{
public:
    LcdMenu(const LiquidCrystal& lcd, const int cols, const int rows)  
		:	lcd(lcd), rows(rows), cols(cols) {
	};
	~LcdMenu();
	
	void setHead(LcdMenuEntry* main);
	LcdMenuEntry* selectEntry(const char id);
	boolean levelUp();
	void display();
	void clear();
	boolean step();
	boolean page();
	boolean stepReverse();
	boolean pageReverse();
		
private:
	LcdMenuEntry* getCurrentTop();
		
	LiquidCrystal lcd;
	LcdMenuEntry* head;
	LcdMenuEntry* current;
	int cols;
	int rows;
};

#endif

