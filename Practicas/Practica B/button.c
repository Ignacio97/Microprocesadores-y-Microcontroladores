#include "button.h"
#include "uart.h"

static button buttons[] = {
		{VOL_DOWN,1,0},
		{PREV_TRACK,1,0},
		{PLAY,1,0},
		{NEXT_TRACK,1,0},
		{VOL_UP,1,0}
	};

/**
	port	button_id	FUNC
	PFO			1		vol down
	PF1			2		prev track
	PF2			3		play/pause
	PF3			4		next track
	PF4			5		vol up
*/
void setup_port() {
	DDRF = 0b11100000;
	PORTF = ~DDRF;
}

ButtonAction checkButton(){
	static uint8_t i = 0;
	static uint8_t act;	

	act = NONE;

		if(!(PINF&1<<i)){
			if(buttons[i].state){
				buttons[i].state = PRESSED;
				buttons[i].hit_time = ms;
			}	
		
		}
		else {
			if(ms-buttons[i].hit_time > DELAY && buttons[i].state==PRESSED){
				buttons[i].state = NOT_PRESSED;
				act = buttons[i].action;
			}
		}

		i= ++i%5;

	return act;
}
