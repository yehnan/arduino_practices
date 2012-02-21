/* Use a switch to control a LED.
  Details and schematic, please see http://yehnan.blogspot.com/2012/02/arduinoled.html
*/
static int ledStatus;
static unsigned long lastDebounceTime;
#define DEBOUNCE_DELAY 200

void setup(){
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  
  ledStatus = LOW;
  digitalWrite(13, ledStatus);
}

void updateLed(){
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTime) > DEBOUNCE_DELAY){
    lastDebounceTime = currentTime;
    
    ledStatus = ledStatus == HIGH ? LOW : HIGH;
    digitalWrite(13, ledStatus);
    Serial.println(ledStatus);
  }
}

void loop(){
  int switchStatus = digitalRead(2);
  
  if(switchStatus == HIGH){
    updateLed();
  }
}

