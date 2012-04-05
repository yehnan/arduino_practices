int inpin1=2;
int inpin2=3;
int inpin3=4;
int inpin4=5;
int inpin5=6;
//int inpin6=7;
int led=8;
int inpinReset = 9;

int randnum;

void reset() {
	randnum = random(1, 6);//random(1, 7);
	digitalWrite(led, LOW);
	Serial.print("randnum=");
	Serial.println(randnum);
	delay(500);
}

void setup() {
	pinMode(inpin1, INPUT);
	pinMode(inpin2, INPUT);
	pinMode(inpin3, INPUT);
	pinMode(inpin4, INPUT);
	pinMode(inpin5, INPUT);
	//pinMode(inpin6, INPUT);

	pinMode(led, OUTPUT);
	pinMode(inpinReset, INPUT);
	Serial.begin(115200);
	
	reset();
}

void loop() {
	switch (randnum) {
		case 1:
			if(digitalRead(inpin1) == HIGH){
				digitalWrite(led, HIGH);
				Serial.println("inpin1");
			}
			break;
		case 2:
			if(digitalRead(inpin2) == HIGH){
				digitalWrite(led, HIGH);
				Serial.println("inpin2");
			}
			break;
		case 3:
			if(digitalRead(inpin3) == HIGH){
				digitalWrite(led, HIGH);
				Serial.println("inpin3");
			}
			break;
		case 4:
			if(digitalRead(inpin4) == HIGH){
				digitalWrite(led, HIGH);
				Serial.println("inpin4");
			}
			break;
		case 5:
			if(digitalRead(inpin5) == HIGH){
				digitalWrite(led, HIGH);
				Serial.println("inpin5");
			}
			break;
	}
	
	if(digitalRead(inpinReset) == HIGH){
		Serial.println("inpinReset");
		reset();
	}
}

