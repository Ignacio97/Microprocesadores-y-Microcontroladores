#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"


/***GLOBAL VARIABLES*/
ring_buffer_t input_queue;
ring_buffer_t output_queue;


/**SIG_USART0_DATA*/
ISR(USART0_UDRE_vect){

  if (OUTPUT_BUFFER_EMPTY) {
    UCSR0B &= ~(1<<UDRIE0);  /**disable interrupt*/
  }
  else{
    output_queue.head = (output_queue.head+1) % BUFFER_SIZE;
    UDR0 = output_queue.buffer[output_queue.head];
  }

}

/*SIG_USART0_RECV*/
ISR(USART0_RX_vect){

    if (!INPUT_BUFFER_FULL) {
        input_queue.tail = (input_queue.tail +1) % BUFFER_SIZE;
        input_queue.buffer[input_queue.tail] = UDR0;
    }

}

void UART0_putchar(char data) {

    while(OUTPUT_BUFFER_FULL);

    output_queue.tail = (output_queue.tail + 1) % BUFFER_SIZE;
    output_queue.buffer[output_queue.tail] = data;

	   UCSR0B |= (1<<UDRIE0);
}

void UART0_puts(char *str){
    while(*str)
      UART0_putchar(*(str++));
}

uint8_t UART0_available(){
    return (!INPUT_BUFFER_EMPTY);
}

char UART0_getchar() {
  static char aux;
  /**waiting for data**/
  while (!UART0_available()) ;

  input_queue.head = (input_queue.head+1)% BUFFER_SIZE;
  aux = input_queue.buffer[input_queue.head];
  UART0_putchar(aux); /**echo*/

  return aux;
}

void UART0_gets(char *str){

        const unsigned char max_size = 20;
        const char *const aux = str;
        static char c;

        c = UART0_getchar();

        while( c != 13) {

                if (c != 8 ) {
                        if ( str < aux + max_size - 1 ) {
                                *(str++) = c;
                        }
                        else {
                                UART0_putchar(8);
                                UART0_putchar(32);
                                UART0_putchar(8);

                        }

                }
                else {
                        if (str == aux) {
                                UART0_putchar(32);
                        }
                        else  {
                                UART0_putchar(32);
                                UART0_putchar(c);
                                str--;
                        }
                }

                c = UART0_getchar();
        }

        UART0_putchar(10); //line feed
        *str = 0;

}
void gotoXY(uint8_t x,uint8_t y) {
  static char str[] = "\x1b[00;00H";


  /**convert dec to char*/
    str[3] = '0' + y % 10;
    y/=10;
    str[2] = '0' + y %10; 

    str[6] = '0' + x % 10;
    x/=10;
    str[5] = '0' + x %10; 

  UART0_puts(str);
}

void setColor(uint8_t color){
    static char str[] = "\x1b[30m";

    switch (color) {
      case BLACK:
          str[3] = '0';
        break;
      case RED:
          str[3] = '1';
        break;
      case GREEN:
          str[3] = '2';
          break;
      case YELLOW:
          str[3] = '3';
        break;
      case BLUE:
          str[3] = '4';
        break;
      case MANETA:
          str[3] = '5';
        break;
      case CYAN:
          str[3] = '6';
        break;
      case WHITE:
          str[3] = '7';
        break;
    }

    UART0_puts(str);
}

void clr_screen(){
    UART0_puts("\x1b[2J");
    UART0_puts("\x1b[H");
}
void UART_init(uint8_t com,uint16_t baud_rate,uint8_t size,uint8_t parity,uint8_t stop){
  uint8_t *base_address;

        base_address = (uint8_t*) 0xc0;


         if (com == 3)
            base_address = (uint8_t*) 0x130;  /* UCSR0 = 0xC0 , UCSR3 = 0x130*/
        else
            while (com--)
                base_address += 0x08;

      /* Enable receiver and transmitter */
        *(base_address + 1) |= (1<<RXEN0) | (1<<TXEN0);


        baud_rate = 16000000/16/baud_rate - 1; /**calculating UBRR value*/

        *(base_address + 5) = 0; /*UBRRH*/
        *(base_address + 4) = (uint8_t) baud_rate; /*UBRRL*/

      /**setting up character size**/
        *(base_address + 1) &= ~(1<<UCSZ02); /*UCRxB*/
        *(base_address + 2) &= ~(1<<UCSZ00) & ~(1<<UCSZ01);/*UCRxC*/

      /*size 5 is set by default above*/
            switch (size) {
                case 6:
                *(base_address + 2) |= (1<<UCSZ00) ;/*UCRxC*/
                break;
                case 7:
                *(base_address + 2) |= (1<<UCSZ01) ;/*UCRxC*/
                break;
                case 8:
                *(base_address + 2) |= (1<<UCSZ00) | (1<<UCSZ01);/*UCRxC*/
                 break;
            }

      /**setting up parity**/

            *(base_address + 2) &= ~(1<<UPM00) & ~(1<<UPM01);/*UCRxC*/

            switch (parity) {
                case 1:
                *(base_address + 2) |= (1<<UPM00) | (1<<UPM01);/*UCRxC*/
                    break;
                case 2:
                *(base_address + 2) |= (1<<UPM01);/*UCRxC*/
                  break;
            }

          /**STOP BIT**/

            if (stop == 2)
                  *(base_address + 2) |= (1<<USBS0);/*UCRxC*/

          /**enable rx and UDRIE interrupt  **/
                *(base_address + 1) |= (1<<RXCIE0) | (1<<UDRIE0); /*UCRxB*/

			input_queue.head = 0;
			input_queue.tail = 0;
			output_queue.head = 0;
			output_queue.tail = 0;

}

unsigned int atoi(const char *str){
        unsigned int number = 0;
        int aux = 0;

        while(*str) {
                aux = *str - '0';
                if (aux >=0 && aux <=9) {
                        number += aux;
                        str++;
                        if(*str >= '0' && *str <= '9') {
                                number *= 10;
                        }
                }
                else{
                        break;
                }
        }

        return number;
}

void itoa(char *str, unsigned int number, unsigned char base){
        char *str_start = str;
        char aux;

        do {
                aux = '0' + number % base;
                *(str++) = (aux > '9') ? aux+7 : aux;
                number /= base;
        } while(number > 0 );

        *(str--) = '\0';

        /*reversing the array*/
        while(str_start < str) {
                aux = *str_start;
                *str_start = *str;
                *str = aux;
                str_start++;
				str--;
        }
}
