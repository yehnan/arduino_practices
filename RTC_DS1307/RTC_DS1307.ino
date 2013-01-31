#include <Wire.h>
#include <Time.h>  
#include <DS1307RTC.h>

void pf(const char *fmt, ... ){
    char tmp[128]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 128, fmt, args);
    va_end (args);
    Serial.print(tmp);
}

void setup()  {
  Serial.begin(115200);
  
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");      
}

void loop()
{
   pf("%d/%d/%d %02d:%02d:%02d\n", year(), month(), day(), hour(), minute(), second()); 
   delay(1000);
}

void serialEvent()
{
  int t = Serial.read();
  int v = 0;
  int temp;
  while((temp = Serial.read()) != -1){
    v = v * 10 + (temp - '0');
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
      break;
  }
  //setTime(h, m, s, d, M, y);
  tmElements_t tm;
  tm.Year = y - 1970;
  tm.Month = M;
  tm.Day = d;
  tm.Hour = h;
  tm.Minute = m;
  tm.Second = s;
  RTC.set(makeTime(tm));
}




