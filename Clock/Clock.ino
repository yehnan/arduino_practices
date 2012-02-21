/* Use 7-segment display to build a clock
  Details please see
  http://yehnan.blogspot.com/2012/02/arduinoseven-segment-display.html
*/

const int minute_0[4] = {2, 3, 4, 5};
const int minute_1[4] = {6, 7, 8, 9};
const int hour_0[4] = {10, 11, 12, 13};
const int hour_1[2] = {A0, A1};

void writeDigit(const int n, const int *pins, const int bit_count);
void setTime(unsigned long h, unsigned long m, unsigned long s);

void setup(){
  Serial.begin(115200);
  for(int i = 0; i < 4; i++){
    pinMode(minute_0[i], OUTPUT);
    pinMode(minute_1[i], OUTPUT);
    pinMode(hour_0[i], OUTPUT);
  }
  pinMode(hour_1[0], OUTPUT);
  pinMode(hour_1[1], OUTPUT);
  
  setTime(7, 32, 0);
}

void writeDigit(const int n, const int *pins, const int bit_count){
  for(int i = 0; i < bit_count; i++){
    digitalWrite(pins[i], (n >> i) & 0x01);
  }
}

// currentTime unit is millisecond, 1 d = 24 hours, 1 hour = 60 minutes, 1 minute = 60 seconds, 1 second = 1000 milliseconds
// 1 day = 24 * 60 * 60 * 1000 = 86400000
#define MILLISECOND_OF_ONE_DAY (24UL * 60UL * 60UL * 1000UL)

unsigned long currentTime;

unsigned long previousTimeMark;

void setTime(unsigned long h, unsigned long m, unsigned long s){
  currentTime = ((h * 60 + m) * 60 + s) * 1000;
  previousTimeMark = millis();
  updateTime(0);
}

void updateTime(const unsigned long timePassed){
  unsigned long h;
  unsigned long m;
  unsigned long s;
  
  currentTime += timePassed;
  if(currentTime >= MILLISECOND_OF_ONE_DAY){
    currentTime -= MILLISECOND_OF_ONE_DAY;
  }

  s = currentTime / 1000;
  m = s / 60;
  s = s % 60;
  h = m / 60;
  m = m % 60;
  
  writeDigit(m % 10, minute_0, 4);
  writeDigit(m / 10, minute_1, 4);
  writeDigit(h % 10, hour_0, 4);
  writeDigit(h / 10, hour_1, 2);
}

int b[4];
int len = 0;
void loop(){
  unsigned long now = millis();
  if(now - previousTimeMark > 1000){
    updateTime(now - previousTimeMark);
    previousTimeMark = now;
  }
  
  int btemp = Serial.read();
  if(btemp != -1){
    if(0x30 <= btemp && btemp <= 0x39){
      b[len] = btemp - 0x30;
      len++;
      if(len == 4){
        setTime(b[0] * 10 + b[1], b[2] * 10 + b[3], 0);
        len = 0;
      }
    }
    else{
      len = 0;
    }
  }
}


