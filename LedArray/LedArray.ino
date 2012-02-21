/* Direct control 16 LEDs.
  Use 74HC595 to control 16 LEDS.
  Details please see http://yehnan.blogspot.com/2012/02/arduino_19.html
*/

#define NUM 16
int leds[NUM] = {
  A3, A2, A1, A0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
};

void setup() {                
  for(int i = 0; i < NUM; i++){
    pinMode(leds[i], OUTPUT); 
  }     
}

void loop() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(leds[i], HIGH);
    delay(200);
    digitalWrite(leds[i], LOW);
  }
  for(int i = NUM-2; i > 0; i--){
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }
}
