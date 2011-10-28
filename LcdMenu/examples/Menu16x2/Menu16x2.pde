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

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_D7, 
                  PIN_LCD_D6, PIN_LCD_D5, PIN_LCD_D4);
LcdMenu menu(lcd, LCD_COLS, LCD_ROWS);

void setup() {
  Serial.begin(115200);
  setupLCD();  
  setupMenu();
}

boolean fwd = true;

void loop() {
  menu.display();
  boolean result;
  if ( fwd ) {
    result = menu.page();
  }
  else {
    result = !menu.pageReverse();
  }
  
  if ( result == fwd ) {
#ifdef DEBUG
  Serial.println("DELAY");
#endif
    delay(2000);
  }

  fwd = result;
}

#define MENU_STAYOPEN   1
#define MENU_AUTOCLOSE  2
#define MENU_LOCKTIMES  3
#define MENU_SETTINGS   4

LcdMenuEntry m1(MENU_STAYOPEN, "Stay Open");
LcdMenuEntry m2(MENU_AUTOCLOSE, "Auto Close");
LcdMenuEntry m3(MENU_LOCKTIMES, "Lock Times");
LcdMenuEntry m4(MENU_SETTINGS, "Settings");

void setupMenu() {
  m1.setSiblings(NULL, &m2);
  m2.setSiblings(&m1, &m3);
  m3.setSiblings(&m2, &m4);
  m4.setSiblings(&m3, NULL);
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

