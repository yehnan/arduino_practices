#include "pitches.h"
#include "SimonSays.h"

#define TONE_PIN A0
#define NUMBER 4
const int switches[NUMBER] = {5, 4, 3, 2};
const int leds[NUMBER] = {11, 10, 9, 8};
const int notes[NUMBER] = {
	NOTE_C4, NOTE_D4, NOTE_E4,NOTE_F4,
};

int q_num = 3;
int *questions = NULL;
int *answers = NULL;
int answer_num = 0;
unsigned long lastClickTime;

State state = STATE_START;

int noteStart[] = {
	NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, 
	NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4
};
int noteDurationsStart[] = {16, 8, 16, 8, 16, 4, 16, 16, 16, 16, 8, 16, 4};

int noteCorrect[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5};
int noteDurationsCorrect[] = {16, 16, 16, 8, 16, 8};

int noteWrong[] = {
	NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_, NOTE_B3, NOTE_C4
};
int noteDurationsWrong[] = {16, 32, 32, 16, 16, 16, 16, 16};

Melody melodys[MELODY_MAX] = {
	{noteStart, noteDurationsStart, 13},
	{noteCorrect, noteDurationsCorrect, 6},
	{noteWrong, noteDurationsWrong, 8},
};

void playtone(int *note, int *noteDurations, int num){
  for(int thisNote = 0; thisNote < num; thisNote++){

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 3000 / noteDurations[thisNote];
    tone(TONE_PIN, note[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    //noTone(8);
  }
}

void playMelody(Melody_Enum me){
	playtone(melodys[me].note, melodys[me].duration, melodys[me].number);
}

void setup(){
	for(int i = 0; i < NUMBER; i++){
		pinMode(switches[i], INPUT);
		digitalWrite(switches[i], HIGH);
		
		pinMode(leds[i], OUTPUT);
		digitalWrite(leds[i], LOW);
	}
	
	randomSeed(analogRead(A1));
}

void reset(){
	free(questions);
	questions = NULL;
	
	answer_num = 0;
	free(answers);
	answers = NULL;
	
	for(int i = 0; i < NUMBER; i++){
		digitalWrite(leds[i], LOW);
	}
}

void playOneTone(int note, float delayScale){
	int noteDuration = 3000 / 8;
    tone(TONE_PIN, note, noteDuration);
	
    int pauseBetweenNotes = noteDuration * delayScale;
    delay(pauseBetweenNotes);

}
void playQuestionsTone(){
	for(int i = 0; i < q_num; i++){
		digitalWrite(leds[questions[i]], HIGH);
		playOneTone(notes[questions[i]], 1.3);
		digitalWrite(leds[questions[i]], LOW);
	}
}

boolean check(){
	for(int i = 0; i < q_num; i++){
		if(questions[i] != answers[i]){
			return false;
		}
	}
	return true;
}

void loop(){
	switch(state){
		case STATE_START:{
			reset();
			playMelody(MELODY_START);
			state = STATE_QUESTION;
			break;
		}
		
		case STATE_QUESTION:{
			questions = (int *)(malloc(sizeof(int) * q_num));
			answers = (int *)(malloc(sizeof(int) * q_num));
			for(int i = 0; i < q_num; i++){
				questions[i] = random(0, NUMBER);
			}
			answer_num = 0;
			playQuestionsTone();
			lastClickTime = millis();
			state = STATE_ANSWER;
			break;
		}
		
		case STATE_ANSWER:{
			const unsigned long nowTime = millis();
			if(nowTime >= lastClickTime + 10000UL){
				state = STATE_WRONG;
				break;
			}
			
			for(int i = 0; i < NUMBER; i++){
				int ss = digitalRead(switches[i]);
				if(ss == LOW){
					digitalWrite(leds[i], HIGH);
					lastClickTime = nowTime;
					answers[answer_num] = i;
					answer_num++;
					playOneTone(notes[i], 1);
					digitalWrite(leds[i], LOW);
					delay(200);
					break;
				}
				
			}
			
			if(answer_num >= q_num){
				state = check() ? STATE_CORRECT : STATE_WRONG;
			}
			break;
		}
		
		case STATE_CORRECT:{
			q_num++;
			playMelody(MELODY_CORRECT);
			delay(2000);
			state = STATE_START;
			break;
		}
		
		case STATE_WRONG:{
			playMelody(MELODY_WRONG);
			delay(2000);
			state = STATE_START;
			break;
		}
		
		default:{
			state = STATE_START;
			break;
		}
	}
}



