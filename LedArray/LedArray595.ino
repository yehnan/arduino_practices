/* Direct control 16 LEDs.
  Use 74HC595 to control 16 LEDS.
  Details please see http://yehnan.blogspot.com/2012/02/arduino_19.html
*/

#define DataPin 2 // to 74HC595 DS
#define LatchPin 3 // to 74HC595 ST_CP
#define ClockPin 4 // to 74HC595 SH_CP

void setup() {               
  pinMode(DataPin, OUTPUT); 
  pinMode(LatchPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
}

void loop() {
  uint8_t number;
  for (int i = 0; i < 8; i++) {
    digitalWrite(LatchPin, LOW);

    number = 0;
    bitSet(number, i);
   
    shiftOut(DataPin, ClockPin, MSBFIRST, number); 

    digitalWrite(LatchPin, HIGH);
    delay(300);
  }
  for (int i = 6; i >=0; i--) {
    digitalWrite(LatchPin, LOW);

    number = 0;
    bitSet(number, i);
   
    shiftOut(DataPin, ClockPin, MSBFIRST, number); 

    digitalWrite(LatchPin, HIGH);
    delay(300);
  }
}

