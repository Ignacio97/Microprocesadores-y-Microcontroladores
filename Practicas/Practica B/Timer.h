#ifndef _TIMER_H
#define _TIMER_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>
#include "songs.h"
#include "button.h"
#include "uart.h"

#define PRESCALER 1024

/*	Definir el macro que calcula los ticks en base a al parametro de frecuencia (f). */
#define TICKS(f) ((16000000/PRESCALER)/(f))

/***variables****/
extern uint32_t ms;
extern uint16_t played_notes;
extern uint8_t volume[];
extern uint8_t volume_index;
extern uint8_t play;

void Timer0_init(void);
void Timer2_Freq_Gen(uint8_t ticks);
void Timer2_Play(const struct note song[],unsigned int len);
void Timer2_Volume(uint8_t direction);



#endif
