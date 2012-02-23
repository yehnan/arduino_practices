/* Use LiquidCrystal library to control 2x16 LCD(Liquid Crystal Display)
  Details please see 
  http://yehnan.blogspot.com/2012/02/arduinoliquidcrystallcdhitachi-hd44780.html
*/

#include <LiquidCrystal.h>
#define ROW_NUM 2
#define COL_NUM 16
#define ROW(x) (x / COL_NUM)
int index = 0;
#define INDEX_MAX (COL_NUM * ROW_NUM)
#define COL(x) (x % COL_NUM)

LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

void setup(){
  Serial.begin(115200);
  lcd.begin(COL_NUM, ROW_NUM);
  lcd.setCursor(0, 0);
  lcd.cursor();
  lcd.blink();
}

void loop(){
  int b;
  while( (b = Serial.read()) != -1){
    if(0x20 <= b && b <= 0x7E){
      if(index == INDEX_MAX - 1){
        index = 0;
        lcd.clear();
      }

      lcd.write(b);
      index++;
      lcd.setCursor(COL(index), ROW(index));
    }
  }
}

