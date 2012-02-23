/* Use a photo resistor to control a LED.
  Details and schematic, please see http://yehnan.blogspot.com/2012/02/arduino_23.html
*/
int pr_min = 400;

void setup(){
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(13, LOW);
}

void loop(){
  int pr = analogRead(A0);
  Serial.println(pr);
  
  digitalWrite(13, pr > pr_min ? LOW : HIGH);
  
  delay(1000);
}

