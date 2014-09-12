#include <Wire.h>
#include <Time.h>  
#include <DS1307RTC.h>
#include <Timer.h>

void pf(const char *fmt, ... ){
    char tmp[128]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 128, fmt, args);
    va_end (args);
    Serial.print(tmp);
}

Timer t;
void outputTime(){
  pf("%d/%d/%d %02d:%02d:%02d\n", year(), month(), day(), hour(), minute(), second()); 
}
#define MAX 5
int buf[MAX];
int len;
void setup()  {
  Serial.begin(38400);
  
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");

  t.every(1000, outputTime);
  
  len = 0;
}

void loop()
{
  //pf("%d/%d/%d %02d:%02d:%02d\n", year(), month(), day(), hour(), minute(), second()); 
  //delay(1000);
  t.update();
}

void processTime(){
  if(len < 2){ // at least one char and one digit
    return;
  }

  int t = buf[0];
  int v = 0;
  int i;
  for(i = 1; i < len; i++){
    v = v * 10 + (buf[i] - '0');
  }
  
  int y = year();
  int M = month();
  int d = day();
  int h = hour();
  int m = minute();
  int s = second();
  
  switch(t){
    case 'y':
      y = v;
      break;
    case 'M':
      M = v;
      break;
    case 'd':
      d = v;
      break;
    case 'h':
      h = v;
      break;
    case 'm':
      m = v;
      break;
    case 's':
      s = v;
      break;
    default:
      pf("Wrong\n");
      return;
      break;
  }

  tmElements_t tm;
  tm.Year = y - 1970;
  tm.Month = M;
  tm.Day = d;
  tm.Hour = h;
  tm.Minute = m;
  tm.Second = s;
  
  setTime(makeTime(tm));
  RTC.set(makeTime(tm));
}
void serialEvent()
{
  int c = Serial.read();
  if(('a' <= c && c <= 'z') ||
     ('A' <= c && c <= 'Z') ||
     ('0' <= c && c <= '9')){
    Serial.println(c);
    buf[len] = c;
    len += 1;
  }
  else{
    processTime();
    len = 0;
  }

  if(len == MAX){
    processTime();
    len = 0;
  }
}

