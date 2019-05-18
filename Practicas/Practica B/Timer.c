 #include "Timer.h"


uint32_t ms = 0;
uint16_t played_notes = 0;

uint8_t volume[] = {0,1,2,8,20,50};
uint8_t volume_index = 0;

uint8_t first = 0;
uint32_t silence_start = 0;
uint8_t play = 0;
uint8_t pause = 0;


//debug
char cad[100];

void Timer0_init( void ){
	/* 	Permanece igual, ocasionando una interrupción cada 1 ms en modo CTC. */
  TCNT0 = 0 ;
  OCR0A = 250 - 1;
  TCCR0A |= (1<<WGM01);  //ctc mode
  TIMSK0 |= (1<<OCIE0A); //Timer/Counter0 Output Compare Match A Interrupt Enable
  TCCR0B |= (1<<CS00) | (1<<CS01);//Timer0 start 64 prescaler
}

/* 	Código para actualizar bandera de segundos */

	/*	Agregar las instrucciones necesarias para reproducir
		la siguiente nota en el arreglo dependiendo de la duración,
		e insertar los silencios entre cada nota. */
	ISR(TIMER0_COMPA_vect){
  				ms++;	

  		if (play){

  				if (first){
  					first = 0;
  					Timer2_Freq_Gen(TICKS(current_song.current_note.freq));
  				}

              	if (!pause){
              		if ((ms-current_song.note_start_time) >= current_song.current_note.delay){
              					pause = 1;
              					silence_start = ms;
            					Timer2_Freq_Gen(0);

              					//read next note to be played
              						current_song.current_note.freq = pgm_read_word(current_song.head+(played_notes*4));
              						current_song.current_note.delay = pgm_read_word(current_song.head+((played_notes*4)+2));
              						played_notes++;

 								
					            if(played_notes-1 == current_song.size){
              							play =0;
              							played_notes = 0;
              					}	
              		}
              		
              	}
              	else if(ms-silence_start >= 10){
              			pause = 0;
 						if (current_song.current_note.freq){
 							Timer2_Freq_Gen(TICKS(current_song.current_note.freq));
 							current_song.note_start_time = ms;
 						}
              	}
  		}

  				
	}  		




void Timer2_Freq_Gen(uint8_t ticks){

		if (ticks == 0){
				TCCR2B = 0; //timer2 off
				
		}
		else{
			
      		TCCR2A =  (3<<WGM20) |(2<<COM2B0); //fast pwd CTC
			TCCR2B = (7<<CS00) | (1<<WGM22); // prescaler set to 1024
			OCR2A = ticks-1;
			Timer2_Volume(NONE); //VOLUME UPDATE
			/*itoa(cad,OCR2B,10);
            UART0_puts(cad);*/
		}

}

void Timer2_Play(const struct note song[],unsigned int len){

    current_song.head = song;
    current_song.size = len;
    //load first note
    current_song.current_note.freq = pgm_read_word(&song[0]);
    current_song.current_note.delay = pgm_read_word(&song[2]);
    first = 1;
    play = 1;
    played_notes = 0;

}

void Timer2_Volume(uint8_t direction){

	if (direction == VOL_UP && volume_index+1 < 6){
		volume_index++;
	}
	else if (direction == VOL_DOWN && volume_index-1 >= 0){
		volume_index--;
	}

	if(!volume[volume_index]){
		TCCR2B = 0;
	}
	else if(play){
		TCCR2B = (7<<CS00) | (1<<WGM22); // prescaler set to 1024
		OCR2B = (OCR2A*volume[volume_index])/100;
	}
	
}
