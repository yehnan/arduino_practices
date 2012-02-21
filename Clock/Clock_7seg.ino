/* Use 7-segment display to build a clock
  Details please see
  http://yehnan.blogspot.com/2012/02/arduinoseven-segment-display.html
*/

#define NUM 8
int pins[NUM] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {               
  for(int i = 0; i < NUM; i++){
    pinMode(pins[i], OUTPUT);   
  }
}

void loop() {
  for(int i = 0; i < NUM; i++){
    digitalWrite(pins[i], HIGH);
  }
  delay(1000);
  for(int i = 0; i < NUM; i++){
    digitalWrite(pins[i], LOW);
  } 
  delay(1000);
}


