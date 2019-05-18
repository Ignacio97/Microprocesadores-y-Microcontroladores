#ifndef _BUTTON_H
#define _BUTTON_H

#include <avr/io.h>
#include "Timer.h"

#define NOT_PRESSED 1
#define PRESSED 0
#define DELAY 100 //ms


typedef enum {
	NONE, VOL_DOWN, VOL_UP, PREV_TRACK, NEXT_TRACK , PLAY
}ButtonAction;

typedef struct{
	uint8_t action;
	uint8_t state;
	uint32_t hit_time;
}button;


void setup_port();
ButtonAction checkButton();

#endif
