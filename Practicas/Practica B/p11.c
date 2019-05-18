#include "uart.h"
#include "Timer.h"
#include "button.h"

int main(){
	char cad[100];

	UART_init(0,0,8,1,2);
	UART0_AutoBaudRate();
	UART0_puts("Autobaud done\n\r");
	Timer0_init();
	setup_port();
	DDRH |= (1<<PH6);

	while(1){
		switch ( checkButton()){
			case VOL_UP:
				UART0_puts("UP\n\r");
				Timer2_Volume(VOL_UP);
						break;
			case VOL_DOWN:
					UART0_puts("down\n\r");
					Timer2_Volume(VOL_DOWN);
				break;

			case NEXT_TRACK:
						UART0_puts("next\n\r");
						
						if (++song_index == songs_counter) song_index = 0;
					Timer2_Play(all_songs[song_index],songs_size[song_index]);
			break;

			case PREV_TRACK:
				UART0_puts("prev\n\r");

				song_index = (!song_index) ? songs_counter-1: --song_index;
				Timer2_Play(all_songs[song_index],songs_size[song_index]);
			break;

			case PLAY:
					UART0_puts("play\n\r");
					Timer2_Play(all_songs[song_index],songs_size[song_index]);
				break;
		/*	case NONE:
					UART0_puts("nonr\n\r");
				break;*/

		}
	}



	return 0;
}
