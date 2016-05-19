#include <SoftwareSerial.h> // 軟體序列埠
#define SERIAL_BAUDRATE 115200

#define X_PIN 2 // MX2125的X軸
#define Y_PIN 3 // MX2125的Y軸

void setup(){
    Serial.begin(SERIAL_BAUDRATE);
    pinMode(X_PIN, INPUT);
    pinMode(Y_PIN, INPUT);
}

void loop(){
    int xraw = pulseIn(X_PIN, HIGH);
    // x，水平時，約是5000，往前傾斜90度 約3800，往後傾斜90度 約6200
    
    int yraw = pulseIn(Y_PIN, HIGH);
    // y，水平時，約是4900，往左傾斜90度 約3700，往右傾斜90度 約6300
    
    Serial.print(xraw);
    Serial.print(" , ");
    Serial.println(yraw);
}
