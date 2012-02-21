/* Use 7-segment display to build a clock
  Details please see
  http://yehnan.blogspot.com/2012/02/arduinoseven-segment-display.html
*/

int pins[4] = {2, 3, 4, 5};

void setup(){
  for(int i = 0; i < 4; i++){
    pinMode(pins[i], OUTPUT);   
  }
}

void writeDigit(int n){
  for(int i = 0; i < 4; i++){
    digitalWrite(pins[i], (n >> i) & 0x01);
  }
}

void loop(){
  for(int n = 0; n <= 9; n++){
    writeDigit(n);
    delay(1000);
  }
}
