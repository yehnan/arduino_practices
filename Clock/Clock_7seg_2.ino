/* Use 7-segment display to build a clock
  Details please see
  http://yehnan.blogspot.com/2012/02/arduinoseven-segment-display.html
*/

#define NUM 8
int pins[NUM] = {2, 3, 4, 5, 6, 7, 8, 9};
#define t true
#define f false
boolean data[10][NUM] = {
  {t, t, t, t, t, t, f, f}, // 0
  {f, t, t, f, f, f, f, f}, // 1
  {t, t, f, t, t, f, t, f}, // 2
  {t, t, t, t, f, f, t, f}, // 3
  {f, t, t, f, f, t, t, f}, // 4
  {t, f, t, t, f, t, t, f}, // 5
  {t, f, t, t, t, t, t, f}, // 6
  {t, t, t, f, f, f, f, f}, // 7
  {t, t, t, t, t, t, t, f}, // 8
  {t, t, t, t, f, t, t, f}, // 9
};

void setup(){                
  for(int i = 0; i < NUM; i++){
    pinMode(pins[i], OUTPUT);    
  } 
}
void writeNumber(int n){
  for(int i = 0; i < NUM; i++){
    digitalWrite(pins[i], data[n][i] == t ? HIGH : LOW);
  }
}
void loop(){
  for(int n = 0; n <= 9; n++){
    writeNumber(n);
    delay(1000);
  }
}


