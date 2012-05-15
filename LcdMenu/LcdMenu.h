#ifndef LCDMENUh
#define LCDMENUh

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "LcdMenuHandler.h"

//#define DBG 0

class LcdMenuEntry {
public:
	LcdMenuEntry(const char id, const char* text, LcdMenuHandler* handler);
	~LcdMenuEntry();
	
	void setChild(LcdMenuEntry* child) { this->child = child; child->parent = this; };	
	void setPrev(LcdMenuEntry* prev) { this->prev = prev; };	
	void setNext(LcdMenuEntry* next) { this->next = next; };	
	void setSiblings(LcdMenuEntry* prev, LcdMenuEntry* next) { this->prev = prev; this->next = next; };	
	void appendSibling(LcdMenuEntry* sibling);
	
	const char getId() { return id; };
	const char* getDisplayText() { return displayText; };
	const char* getText() { return text; };
	LcdMenuEntry* getParent() { return parent; };
	LcdMenuEntry* getChild() { return child; };
	LcdMenuEntry* getPrev() { return prev; };
	LcdMenuEntry* getNext() { return next; };
	LcdMenuHandler* getHandler() { return handler; };
	
private:
	const int id;
	const char* text;
	char* displayText;
	LcdMenuEntry* parent;
	LcdMenuEntry* child;
	LcdMenuEntry* prev;
	LcdMenuEntry* next;
	LcdMenuHandler* handler;
};

class LcdMenu
{
public:
    LcdMenu(LiquidCrystal* lcd, const int cols, const int rows);
	~LcdMenu();
	
	void setHead(LcdMenuEntry* main);
	LcdMenuHandler* procKeyPress(const char id);
	boolean levelUp();
	void reset() { current = head; };
	void display();
	void clear();
	boolean step();
	boolean page();
	boolean stepReverse();
	boolean pageReverse();
		
private:
	LcdMenuEntry* getCurrentTop();
		
	LiquidCrystal* lcd;
	LcdMenuEntry* head;
	LcdMenuEntry* current;
	int cols;
	int rows;
};

#endif

