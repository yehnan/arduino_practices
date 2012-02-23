/* Use LiquidCrystal library to control 2x16 LCD(Liquid Crystal Display)
  Details please see 
  http://yehnan.blogspot.com/2012/02/arduinoliquidcrystallcdhitachi-hd44780.html
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

void setup(){
  lcd.begin(16, 2);
  lcd.print("Hello, World!");
}

void loop(){
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}

