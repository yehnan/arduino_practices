#ifndef SimonSays_h
#define SimonSays_h

typedef struct{
	int *note;
	int *duration;
	int number;
}Melody;
typedef enum{
	MELODY_START,
	MELODY_CORRECT,
	MELODY_WRONG,
	MELODY_MAX,
} Melody_Enum;
typedef enum{
	STATE_START,
	STATE_QUESTION,
	STATE_ANSWER,
	STATE_CORRECT,
	STATE_WRONG,
	STATE_MAX,
} State;

#endif
