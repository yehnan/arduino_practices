#include "bar.h"

ClassBar::ClassBar(){
	delayDuration = 0;
}

int ClassBar::getDelayDuration(){
	delayDuration += 100;
	return delayDuration;
}

