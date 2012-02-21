#include <arduino.h>
#include "foo.h"
#include "bar.h"

void setup(){
	Serial.begin(115200);
	pinMode(13, OUTPUT);     
}

ClassBar bar;

void loop(){
  int dt = delayDuration();
  int bardt = bar.getDelayDuration();
  
  digitalWrite(13, HIGH);
  delay(dt);
  digitalWrite(13, LOW);
  delay(bardt);
  
  Serial.println(dt);
  Serial.println(bardt);
}

