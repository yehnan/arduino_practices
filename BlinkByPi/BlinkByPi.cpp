#include <Arduino.h>

void setup(){
	Serial.begin(115200);
	pinMode(13, OUTPUT);
}

void loop(){
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}

