#include <Bounce.h>

Bounce bouncer = Bounce(2, 50);
static int ledStatus = LOW;

void setup(){
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop(){
  if(bouncer.update() == true && bouncer.read() == HIGH) {
    ledStatus = ledStatus == HIGH ? LOW : HIGH;
    digitalWrite(13, ledStatus);
  }
}

