// 匯入所需程式庫的標頭檔
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#include "pitches.h" // 音符頻率

#define SERIAL_BAUDRATE 115200
#define BUZZER_PIN 5 // 蜂鳴器或小喇叭連接腳位

// 定義矩陣鍵盤的針腳（A~H，從左至右）與Arduino腳位的連接關係
#define A_PIN 13
#define B_PIN 12
#define C_PIN 11
#define D_PIN 10
#define E_PIN 9
#define F_PIN 8
#define G_PIN 7
#define H_PIN 6

#define COL 4 // 矩陣鍵盤有4直欄
#define ROW 4 // 矩陣鍵盤有4橫列

// 定義矩陣鍵盤的針腳（A~H，從左至右）與列欄的關係
#define COL_0_PIN A_PIN
#define COL_1_PIN B_PIN
#define COL_2_PIN C_PIN
#define COL_3_PIN D_PIN
#define ROW_0_PIN E_PIN
#define ROW_1_PIN F_PIN
#define ROW_2_PIN G_PIN
#define ROW_3_PIN H_PIN

#define CHAR_1 '1'
#define CHAR_2 '2'
#define CHAR_3 '3'
#define CHAR_4 '4'
#define CHAR_5 '5'
#define CHAR_6 '6'
#define CHAR_7 '7'
#define CHAR_8 '8'
#define CHAR_9 '9'
#define CHAR_0 '0'
#define CHAR_STAR '*'
#define CHAR_SHARP '#'
#define CHAR_A 'A'
#define CHAR_B 'B'
#define CHAR_C 'C'
#define CHAR_D 'D'

#define CHAR_SPACE ' ' // 代表「無」

void pf(const char *fmt, ... ){
    char tmp[128]; // resulting string limited to 128 chars
    va_list args;
    va_start (args, fmt );
    vsnprintf(tmp, 128, fmt, args);
    va_end (args);
    Serial.print(tmp);
}

#define NUMBER (COL * ROW) // 按鍵數目

char chars[NUMBER] = {
    CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHAR_5,
    CHAR_6, CHAR_7, CHAR_8, CHAR_9, CHAR_0,
    CHAR_STAR, CHAR_SHARP,
    CHAR_A, CHAR_B, CHAR_C, CHAR_D,
};

byte rowPins[ROW] = {ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN};
byte colPins[COL] = {COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN};
char keys[ROW][COL] = { // 每個按鍵所對應的字元
  {CHAR_1, CHAR_2, CHAR_3, CHAR_A},
  {CHAR_4, CHAR_5, CHAR_6, CHAR_B},
  {CHAR_7, CHAR_8, CHAR_9, CHAR_C},
  {CHAR_STAR, CHAR_0, CHAR_SHARP, CHAR_D}
};
// 建立Keypad物件
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROW, COL);

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TIME_LIMIT (99UL * 1000UL) // 遊戲時間超過99秒就game over
#define ERROR_MAX 6 // 錯6次就game over
unsigned long game_start_time; // 遊戲開始時的時間
unsigned long q_more_next_time; // 下次放上更多字元的時間
int score;
#define Q_MAX 30 // 出題數目最大值，答對此個數便過關
int q_num = 0; // 已出題數目
int answer_num = 0; // 已達題數目
int error_num = 0; // 答錯數目

typedef struct{
    char ch; // 顯示的字元，若是CHAR_SPACE代表「無」
    unsigned long time; // 顯示該字元的時間
} Data;
Data data[NUMBER];

// 取得下一個可放置字元的索引值
int next_data_index(){
    if(q_num == NUMBER){
        return NUMBER;
    }
    
    int i = random(0, NUMBER);
    while(data[i].ch != CHAR_SPACE){
        i++;
        i %= NUMBER;
        pf("next_data_index i=%d\n", i);
    }
    return i;
}

// 除錯用
void print_data(){
    for(int i = 0; i < NUMBER; i++){
        pf("%X ", i);
    }
    Serial.println("");
    for(int i = 0; i < NUMBER; i++){
        pf("%c ", data[i].ch);
    }
    Serial.println("\n-----------------\n");
}

void more_q(){ // 放上更多字元到LCD
    if(q_num < NUMBER){
        const int cnt = random(1, min(NUMBER - q_num, 3)+1);
        pf("q_num=%d, cnt=%d\n", q_num, cnt);
        for(int n = 0; n < cnt; n++){
            int i = next_data_index();
            if(0 <= i && i < NUMBER){
                data[i].ch = chars[random(0, NUMBER)];
                pf("i=%d, ch=%c\n", i, data[i].ch);
                data[i].time = millis();
                
                q_num++;
                
                lcd.setCursor(i, 0); // (col, row)
                lcd.print(data[i].ch);
                // update_lcd_row0_flag = true;
                print_data();
            }
        }
    }
}

int notes[NUMBER] = { // 音符（發聲頻率）
    NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, 
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, 
    NOTE_C6, NOTE_D6,
};
int beats[NUMBER] = { // 每個音符的發聲時間，8代表八分音符
    8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8,
    8, 8,
};

void play(int *notes, int *beats, int num){
    for(int i = 0; i < num; i++){
        const int note = notes[i];
        const int beat = 3000 / beats[i];
        tone(BUZZER_PIN, note, beat);
        delay(beat * 1.20);
    }
}

bool input_key(char c){
    for(int i = 0; i < NUMBER; i++){
        if(data[i].ch == c){
            const unsigned long delta = millis() - data[i].time;
            
            data[i].ch = CHAR_SPACE;
            data[i].time = 0;
            lcd.setCursor(i, 0);
            lcd.print(CHAR_SPACE);
            q_num--;
            answer_num++;
            
            if(delta >= 3000){ // 根據按鍵速度，計算分數
                score += 1;
            }
            else if(delta >= 2500){
                score += 2;
            }
            else if(delta >= 2000){
                score += 4;
            }
            else if(delta >= 1500){
                score += 6;
            }
            else if(delta <= 1000){
                score += 8;
            }
            else{
                score += 10;
            }
            
            tone(BUZZER_PIN, NOTE_B5, 3000 / 8);
            return true;
        }
    }
    
    error_num++;
    tone(BUZZER_PIN, NOTE_C8, 3000 / 8);
    return false;
}

// 兩隻老虎
int notes_tigers[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, 
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_F4, NOTE_G4, 
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  NOTE_C4, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_G3, NOTE_C4, 
};
int beats_tigers[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 4, 8, 8, 4,
  16, 16, 16, 16, 8, 8,
  16, 16, 16, 16, 8, 8,
  8, 8, 4, 8, 8, 4,
};

char z1;

// 狀態機的可能狀態
typedef enum{
    STATE_START,    // 初始
    STATE_QA,       // 出題與答題
    STATE_ERROR,    // 錯題太多
    STATE_SLOW,     // 答題太慢
    STATE_SUCCESS,   // 過關
    STATE_END,      // 播放兩隻老虎
} State;
State state;

void setup(){
    Serial.begin(SERIAL_BAUDRATE);
    randomSeed(analogRead(A0));
    
    for(int i = 0; i < NUMBER; i++){
        data[i].ch = CHAR_SPACE;
        data[i].time = 0;
    }
    
    lcd.begin(); 
    lcd.backlight();
    lcd.clear();
    
    state = STATE_START;
}

void update_lcd_time(unsigned long t){
    static unsigned long time_updated = t;
    if(t - time_updated >= 1000){
        lcd.setCursor(0, 1);
        lcd.print("Time:");
        time_updated = t;
        lcd.print((game_start_time + TIME_LIMIT - time_updated) / 1000);
        
        lcd.print("Score:");
        lcd.print(score);
    }
}

void loop(){
    switch(state){
        case STATE_START:{ // 初始，播放全部音符
            lcd.setCursor(0, 0);
            lcd.print("Are you ready?");
            
            play(notes, beats, sizeof(notes)/sizeof(int));
            delay(1000);
            
            state = STATE_QA;
            game_start_time = millis();
            q_more_next_time = game_start_time + 1500;
            q_num = 0;
            answer_num = 0;
            error_num = 0;
            score = 0;

            lcd.clear();
            state = STATE_QA;
        }
        break;
        
        case STATE_QA:{
            const unsigned long t = millis();
            update_lcd_time(t);
            
            if(t - game_start_time > TIME_LIMIT){ // time limit
                state = STATE_SLOW;
            }
            
            // 玩家按鍵，判斷是否正確
            const char key = keypad.getKey();
            if(key != NO_KEY){
                input_key(key);
                if(answer_num >= Q_MAX){
                    state = STATE_SUCCESS;
                }
                if(error_num >= ERROR_MAX){
                    state = STATE_ERROR;
                }
            }
            
            // 經過一段時間，再放上更多個字元
            if(t >= q_more_next_time){
                q_more_next_time = t + random(1000, 3000);
                more_q();
            }
        }
        break;
        
        case STATE_SUCCESS:{
            // 分數
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Congratulations");
            lcd.setCursor(0, 1);
            lcd.print("Score: ");
            lcd.print(score);
            
            state = STATE_END;
        }
        break;
        
        case STATE_ERROR:{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Game Over");
            lcd.setCursor(0, 1);
            lcd.print("Too many errors!");
            
            delay(3000);
        }
        break;

        case STATE_SLOW:{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Game Over");
            lcd.setCursor(0, 1);
            lcd.print("You're too slow!");
            
            delay(3000);
        }
        break;
        
        case STATE_END:{
            play(notes_tigers, beats_tigers, sizeof(notes_tigers)/sizeof(int));
            delay(3000);
        }
        break;
    }   
}

