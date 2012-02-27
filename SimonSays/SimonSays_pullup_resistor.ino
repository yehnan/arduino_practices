
void setup(){
	Serial.begin(115200);
	pinMode(13, OUTPUT);
	pinMode(5, INPUT);
	digitalWrite(5, HIGH);
}



void loop(){
	int status = digitalRead(5);
	digitalWrite(13, status);
	Serial.println(status);
}

