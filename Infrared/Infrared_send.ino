#include <IRremote.h>

IRsend irsend; // Digital Pin 3

void setup()
{
  Serial.begin(115200);
}

void loop() {
  int d;
  if( (d = Serial.read()) != -1) {
    unsigned long v = 0x0;
    switch(d){
      case '1':
        v = 0x77E14050;
      break;
      case '2':
        v = 0x77E12050;
      break;
      case '3':
        v = 0x77E1D050;
      break;
      case '4':
        v = 0x77E1B050;
      break;
      case '5':
        v = 0x77E1E050;
      break;
      case '6':
        v = 0x77E11050;
      break;
    }
    
    if(v != 0x0){
      Serial.print("read ");
      Serial.print(d);
      Serial.print(", IR send ");
      Serial.println(v, HEX);
      irsend.sendNEC(v, 32);
    }
  }
}
