/* Use a buzzer and tone() to play a melody.
  Details please see http://yehnan.blogspot.com/2012/02/arduinoloudspeaker.html
*/

#include "pitches.h"

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4};

int melodySister[] = {
  NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, 
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_A3, NOTE_G3, 
  NOTE_A3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_E4, 
  NOTE_D4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4, 
};

int noteDurationsSister[] = {
  6, 16, 8, 8, 8, 8, 4, 
  6, 16, 8, 8, 8, 8, 4, 
  6, 16, 8, 8, 8, 8, 4,
  6, 16, 8, 8, 8, 8, 4,
};

int melodyVase[] = {
  NOTE_, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_,
  NOTE_, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_,
  
  NOTE_, NOTE_G3, NOTE_A3, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_,
  NOTE_, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_,
  
  NOTE_, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_,
  NOTE_, NOTE_G3, NOTE_A3, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_,
  
  NOTE_, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4,
  NOTE_C4, NOTE_A3, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_,
  //
  NOTE_, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_A3, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_,
  NOTE_, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G3, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_C4, NOTE_,
  
  NOTE_, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_,
  NOTE_, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_,
  
  NOTE_, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_A3, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_,
  NOTE_, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G3, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_C4, NOTE_,
  
  NOTE_, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_G3, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_,
};

int noteDurationsVase[] = {
  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  
  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 8,
  16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 8, 8,
  
  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  
  16, 16, 16, 16, 16, 16, 16, 16, 8,
  16, 16, 16, 16, 16, 16, 8, 16, 4, 8,
  //
  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 4, 8,
  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 4, 8,
  
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 4, 8,
  16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 8,
  
  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 4, 8,
  16, 16, 16, 16, 16, 16, 8, 16, 16, 16, 16, 4, 8,
  
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 4, 
  16, 8, 16, 16, 16, 4, 8, 
};

void play(int *melody, int *noteDurations, int num){
  for(int thisNote = 0; thisNote < num; thisNote++){

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 3000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    //noTone(8);
  }
}

void setup(){
  delay(5000);
  play(melodyVase, noteDurationsVase, sizeof(melodyVase) / sizeof(int));
}

void loop(){
  play(melody, noteDurations, 8);
  
  delay(2000);
  
  play(melodySister, noteDurationsSister, sizeof(melodySister) / sizeof(int));
  
  delay(2000);
  
  play(melodyVase, noteDurationsVase, sizeof(melodyVase) / sizeof(int));
  
  delay(2000);
}

