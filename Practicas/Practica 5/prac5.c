#include "timer.h"


void UpdateClock(void);
void DisplayClock(void);
void PrintDec2d(byte);
void Delay(byte);
void setClock(byte,byte,byte);

byte hour,min,seg;


void main(){

        Timer_Ini();

        for(;;) {
                if(TimerSecFlag()) {
                        UpdateClock();
                        DisplayClock();
                        poke(0x0,0xffff,seg);
                }

                Delay(100);

        }
}

void UpdateClock(void){
		seg++;
		if (seg == 60){
			seg = 0;
			min++;
			if (min == 60){
				min = 0; 
				hour = ++hour % 24;
			}
		}

        enter();
}

void DisplayClock(void){
        PrintDec2d(hour);
        putchar(':');
        PrintDec2d(min);
        putchar(':');
        PrintDec2d(seg);
}

void Delay(byte i){
        while(--i);
}

void PrintDec2d(byte dato){
        putchar(dato/10+'0');
        putchar(dato%10+'0');
}
void setClock(byte h,byte m, byte s){
        hour = h;
        min = m;
        seg = s;
}
