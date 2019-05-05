#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"



int main() {
  char cad[20],a;
  uint16_t num;

	sei();
	UART_init(0,12345,8,1,2);

	 while(true){
    UART0_getchar();
    clr_screen();
    gotoXY(2,2);
    setColor(YELLOW);
    UART0_puts("Give me a number: ");

    
    gotoXY(22,2);
    setColor(GREEN);
    UART0_gets(cad);

    num = atoi(cad);
    itoa(cad,num,16);

    gotoXY(5,3);
    setColor(BLUE);
    UART0_puts("Hex:");
    UART0_puts(cad);

    itoa(cad,num,2);

    gotoXY(5,4);
    UART0_puts("Bin:");
    UART0_puts(cad);

    }



  return 0;
}

    
