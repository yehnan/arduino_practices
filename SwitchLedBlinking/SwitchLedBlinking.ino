#define LED_PIN 13
#define SWITCH_PIN 12

#define DEBOUNCE_DELAY 200
unsigned long lastDebounceTime;
int ledBlinkStatus;

#define LED_BLINK_TIME 300
unsigned long lastUpdateLedTime;
int ledStatus = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
}
void updateLedBlinkStatus(){
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTime) > DEBOUNCE_DELAY){
    lastDebounceTime = currentTime;
    ledBlinkStatus = !ledBlinkStatus;
  }
}
void updateLed(){
  if(ledBlinkStatus){
    unsigned long currentTime = millis();
    if((currentTime - lastUpdateLedTime) > LED_BLINK_TIME){
      lastUpdateLedTime = currentTime;
      ledStatus = !ledStatus;
    }
  }
  else{
    ledStatus = LOW;
  }
  digitalWrite(LED_PIN, ledStatus);
}
void loop() {
  int switchStatus = digitalRead(SWITCH_PIN);
  if(switchStatus == HIGH){
    updateLedBlinkStatus();
  }
  updateLed();
}

