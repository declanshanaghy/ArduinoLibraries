#include <LcdMenu.h>
#include <LiquidCrystal.h>

#define DEBUG 1

#define PIN_LCD_BL_PWR   3
#define PIN_LCD_RS      13
#define PIN_LCD_EN       4
#define PIN_LCD_D4      12
#define PIN_LCD_D5      11
#define PIN_LCD_D6      10
#define PIN_LCD_D7       9

#define LCD_COLS 16
#define LCD_ROWS 2

//LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D7, 
//                  PIN_LCD_D6, PIN_LCD_D5, PIN_LCD_D4);
LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D7, 
                  PIN_LCD_D6, PIN_LCD_D5, PIN_LCD_D4);
LcdMenu menu(lcd, LCD_COLS, LCD_ROWS);

void setup() {
  Serial.begin(115200);
  setupLCD();  
  setupMenu();
  menu.display();
}

void loop() {
  if (Serial.available()) {
    int ch = Serial.read();
    if ( ch == 'w' ) {
      if (menu.pageReverse())
        menu.display();
    }
    else if ( ch == 's' ) {
      if (menu.page())
        menu.display();
    }
    else if ( ch == 'a' ) {
      if (menu.stepReverse())
        menu.display();
    }
    else if ( ch == 'd' ) {
      if (menu.step())
        menu.display();
    }
    else if ( ch == '0' ) {
      if (menu.levelUp())
        menu.display();
    }
    else {
      //selectEntry will display a sub menu or call a handler 
      //for the supported entry in the current heirarchy or return
      //false if neither of the previous things happen
      LcdMenuEntry* selected = menu.selectEntry(ch);
      
      if ( selected != NULL ) {
        Serial.print("SELECTED: "); Serial.println(selected->getText());
        menu.display();
      }
      else {
        Serial.println("Unsupported operation"); 
      }
    }
  }
}

void menu1() {
  Serial.println("Menu 1 handler");
}

void menu42() {
  Serial.println("Menu 4-2 handler");
}

#define MENU_1  '1'
#define MENU_2  '2'
#define MENU_3  '3'
#define MENU_4  '4'
#define MENU_5  '5'
#define MENU_6  '6'
#define MENU_7  '7'
#define MENU_41 '1'
#define MENU_42 '2'
#define MENU_43 '3'

LcdMenuEntry m1(MENU_1, "One", &menu1);
LcdMenuEntry m2(MENU_2, "Two", NULL);
LcdMenuEntry m3(MENU_3, "Three", NULL);
LcdMenuEntry m4(MENU_4, "Four", NULL);
LcdMenuEntry m5(MENU_5, "Five", NULL);
LcdMenuEntry m6(MENU_6, "Six", NULL);
LcdMenuEntry m7(MENU_7, "Seven", NULL);
LcdMenuEntry m41(MENU_41, "4-One", NULL);
LcdMenuEntry m42(MENU_42, "4-Two", &menu42);
LcdMenuEntry m43(MENU_43, "4-Three", NULL);

void setupMenu() {
  m1.setSiblings(NULL, &m2);
  m2.setSiblings(&m1, &m3);
  m3.setSiblings(&m2, &m4);
  m4.setSiblings(&m3, &m5);
  m5.setSiblings(&m4, &m6);
  m6.setSiblings(&m5, &m7);
  m7.setSiblings(&m6, NULL);
  m4.setChild(&m41);
  m41.setSiblings(NULL, &m42);
  m42.setSiblings(&m41, &m43);
  m43.setSiblings(&m43, NULL);
  
  menu.setHead(&m1);
}

void setupLCD() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(LCD_COLS, LCD_ROWS);
  // Print a message to the LCD.
  lcd.print("FECK");
  
  pinMode(PIN_LCD_BL_PWR, OUTPUT); 
  enableLCD();
}

void enableLCD() {
    lcd.display();
    digitalWrite(PIN_LCD_BL_PWR, HIGH);
    Serial.println("LCD ON");
}

void disableLCD() {
    lcd.noDisplay();
    digitalWrite(PIN_LCD_BL_PWR, LOW);
    Serial.println("LCD OFF");
}

