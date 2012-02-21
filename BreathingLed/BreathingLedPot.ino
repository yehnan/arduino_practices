/* A Led has breathing effect. 
  Use potentiometer to control the duration of a breathing cycle.
  Details please see http://yehnan.blogspot.com/2012/02/arduino_16.html
*/

int brightness = 0;
int fadeAmount = 5;
int delayDuration = 30;

void setup()  {
  pinMode(3, OUTPUT);
}

void loop()  {
  analogWrite(3, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount ;
  }    

  delay(delayDuration);
  
  int potValue = analogRead(A0);
  delayDuration = map(potValue, 0, 1023, 1, 50);
}

