#include <Bounce.h>
#include <Timer.h>

#define LED_PIN 13
#define SWITCH_PIN 12

#define DEBOUNCE_DELAY 50
int ledBlinkStatus = 0;
Bounce bouncer = Bounce(SWITCH_PIN, DEBOUNCE_DELAY);

#define LED_BLINK_TIME 300
Timer timer;
int8_t timer_id;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}
void loop() {
  if(bouncer.update() == true && bouncer.read() == HIGH){
    ledBlinkStatus = !ledBlinkStatus;
    if(ledBlinkStatus){
      timer_id = timer.oscillate(LED_PIN, LED_BLINK_TIME, HIGH);
    }
    else{
      timer.stop(timer_id);
      digitalWrite(LED_PIN, LOW);
    }
  }

  timer.update();
}

