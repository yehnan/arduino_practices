/* Use 7-segment display to build a clock
  Details please see
  http://yehnan.blogspot.com/2012/02/arduinoseven-segment-display.html
*/

const int minute_0[4] = {2, 3, 4, 5};
const int minute_1[4] = {6, 7, 8, 9};
const int hour_0[4] = {10, 11, 12, 13};
const int hour_1[2] = {A0, A1};

void writeDigit(const int n, const int *pins, const int bit_count){
  for(int i = 0; i < bit_count; i++){
    digitalWrite(pins[i], (n >> i) & 0x01);
  }
}

void setup(){
  Serial.begin(115200);
  for(int i = 0; i < 4; i++){
    pinMode(minute_0[i], OUTPUT);
    pinMode(minute_1[i], OUTPUT);
    pinMode(hour_0[i], OUTPUT);
  }
  pinMode(hour_1[0], OUTPUT);
  pinMode(hour_1[1], OUTPUT);
  
  writeDigit(0, minute_0, 4);
  writeDigit(0, minute_1, 4);
  writeDigit(0, hour_0, 4);
  writeDigit(0, hour_1, 2);
}

void loop(){
  for(int i = 0; i <= 9; i++){
    writeDigit(i, minute_0, 4);
    writeDigit(i, minute_1, 4);
    writeDigit(i, hour_0, 4);
    writeDigit(i % 3, hour_1, 2);
    delay(1000);
  }
}


