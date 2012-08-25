/* Use a switch to control a LED.
  Details and schematic, please see http://yehnan.blogspot.com/2012/02/arduinoled.html
*/
#include <Bounce.h>

Bounce bouncer = Bounce(2, 50);
static int ledStatus = LOW;

void setup(){
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, ledStatus);
}

void loop(){
  bouncer.update();
  if(bouncer.read() == HIGH) {
    ledStatus = bouncer.duration() >= 5000 ? LOW : HIGH;
  }
  else{
    ledStatus = LOW;
  }

  digitalWrite(13, ledStatus);
}


