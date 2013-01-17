#include <PwmLed.h>

#define LED0 9
#define LED1 10
#define LED2 11

PwmLed led0;

void setup()  {
  led0.set(LED0, 0, 5, 30);
}

void loop()  {
  led0.update();                          
}
