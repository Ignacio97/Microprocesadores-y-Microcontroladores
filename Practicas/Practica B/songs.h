#ifndef _SONGS_H
#define _SONGS_H
#include <avr/pgmspace.h>

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 466
#define b 494
#define aa 	493
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880
#define hH 	987
#define bL 247
#define fS 370
#define cS 277
#define aL 220
#define gL 196
#define dS 311
#define gSL 208
#define cL 131
#define eL 165
#define aSL 233

#define TEMPO	500
#define TEMPO_500 500
#define TEMPO_250 250
#define TEMPO_600 600
#define SILENCE 10

#define TOTAL_SONGS 5


struct note{
	uint16_t freq;
	uint16_t delay;
};

typedef struct{
    PGM_P head; //flash pointer to song
    uint16_t size;//total of notes
    uint32_t note_start_time;
    struct note current_note;
}song;


/**variables*/
extern PROGMEM const struct note ImperialMarch[];
extern PROGMEM const struct note AngelesAzules[];
extern PROGMEM const struct note DragonBallGT[];
extern PROGMEM const struct note Clocks[];
extern PROGMEM const struct note Mario[];
extern PGM_P const all_songs[];

extern uint8_t song_index;
extern song current_song;
const uint8_t songs_counter;

extern const uint16_t songs_size[];

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#define GET_TOTAL_SONGS (ARRAY_SIZE(all_songs))

#endif
