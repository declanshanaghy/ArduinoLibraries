#ifndef LCDMENU_h
#define LCDMENU_h

#include <WProgram.h>
#include <LiquidCrystal.h>

#define DEBUG 1

class LcdMenuEntry {
public:
	LcdMenuEntry(const short id, const char* text);
	~LcdMenuEntry();
	
	void setChild(LcdMenuEntry* child) { _child = child; };	
	void setPrev(LcdMenuEntry* prev) { _prev = prev; };	
	void setNext(LcdMenuEntry* next) { _next = next; };	
	void setSiblings(LcdMenuEntry* prev, LcdMenuEntry* next) { _next = next; };	
	
	char* displayText;
	LcdMenuEntry* _child;
	LcdMenuEntry* _prev;
	LcdMenuEntry* _next;
	
private:
	const short _id;
	const char* _text;
};

class LcdMenu
{
public:
    LcdMenu(const LiquidCrystal& lcd, const int cols, const int rows)  
		:	_lcd(lcd), _rows(rows), _cols(cols), _curRow(0) {
	};
	~LcdMenu();
	
	void setHead(LcdMenuEntry* main);
	void display();
	void clear();
	boolean advance();
	boolean reverse();
	void displayCurrent();
		
private:
	LiquidCrystal _lcd;
	LcdMenuEntry* _head;
	LcdMenuEntry* _current;
	int _cols;
	int _rows;
	int _curRow;
};

#endif

