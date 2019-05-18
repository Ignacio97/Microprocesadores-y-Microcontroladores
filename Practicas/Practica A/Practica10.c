#include <avr/io.h>
#include<avr/interrupt.h>
#include "timer0.h"
#include "timer2.h"
#include "uart.h"


void Clock_Update(void);
void Clock_Display(void);
void PrintDec2d(uint8_t dato);
void Clock_Ini(uint8_t h,uint8_t m, uint8_t s);


/**global variables**/
uint8_t hour,min,seg,base;

base=7;

int main(){
   char str[120];

/* llamar a función para inicializar puertos E/S */ /* llamar a función para inicializar UART0 */
		sei();
        UART_init(0,0,8,1,2);
        UART0_AutoBaudRate();
        clr_screen();
        gotoXY(5,1);
        UART0_puts("Autobauding done. UBRR0=");
        itoa(str,UBRR0,10);
        UART0_puts(str);
        UART0_puts("\n\r");
       

       Timer0_Ini();
        Timer2_Ini(base);
        Clock_Ini(23,58,50);

        while(1) {

                if(Timer2_Flag()) {
                        Clock_Update();
                        gotoXY(5,2);
                        Clock_Display();
                        gotoXY(5,3);
                        UART0_puts("millis=");
                        itoa(str,(uint16_t)millis(),10);
                        UART0_puts(str);
                }
        } 

        return 0; 
}
void Clock_Update(void){
		seg++;
		if (seg >= 60){
			seg =  seg - 60;
			min++;
			if (min == 60){
				min = 0;
				hour = ++hour % 24;
			}
		}

}

void Clock_Display(void){
        PrintDec2d(hour);
        UART0_putchar(':');
        PrintDec2d(min);
        UART0_putchar(':');
        PrintDec2d(seg);
}

void PrintDec2d(uint8_t dato){
        UART0_putchar(dato/10+'0');
        UART0_putchar(dato%10+'0');
}
void Clock_Ini(uint8_t h,uint8_t m, uint8_t s){
        hour = h;
        min = m;
        seg = s;
}
