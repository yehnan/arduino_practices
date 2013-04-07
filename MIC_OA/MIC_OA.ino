
int MIC_PIN = A0;

void setup()
{
  Serial.begin(115200);
  pinMode(MIC_PIN, INPUT);     
}
int count = 0;
void loop()
{
  int mic = analogRead(MIC_PIN);
  
  if(mic >= 500){
    count++;
    Serial.print("mic >= 500, count=");
    Serial.println(count);
  }

  //delay(100);
}

