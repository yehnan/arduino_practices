#include <Servo.h> 
 
Servo myservo;

void setup() 
{ 
  myservo.attach(9, 500, 2400);
  myservo.write(90);
  delay(3000);
} 

void loop() 
{
  for(int i = 500; i <= 2400; i+=100){
    myservo.writeMicroseconds(i);
    Serial.println(i);
    delay(300);
  }
  for(int i = 2400; i >= 500; i-=100){
    myservo.writeMicroseconds(i);
    Serial.println(i);
    delay(300);
  }
}

