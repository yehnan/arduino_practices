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
  uint16_t number;
  uint8_t highbyte;
  uint8_t lowbyte;
  for (int i = 0; i < 16; i++) {
    digitalWrite(LatchPin, LOW);

    number = 0;
    bitSet(number, i);
    highbyte = (number >> 8) & 0xFF;
    lowbyte = number & 0xFF;
   
    shiftOut(DataPin, ClockPin, MSBFIRST, highbyte);
    shiftOut(DataPin, ClockPin, MSBFIRST, lowbyte);

    digitalWrite(LatchPin, HIGH);
    delay(100);
  }
  for (int i = 0; i < 16; i++) {
    digitalWrite(LatchPin, LOW);

    number = 0;
    bitSet(number, i);
    highbyte = (number >> 8) & 0xFF;
    lowbyte = number & 0xFF;

    shiftOut(DataPin, ClockPin, LSBFIRST, lowbyte);
    shiftOut(DataPin, ClockPin, LSBFIRST, highbyte);

    digitalWrite(LatchPin, HIGH);
    delay(100);
  }
}

