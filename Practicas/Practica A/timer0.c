#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>

volatile uint32_t ms;

void Timer0_Ini ( void ){
 
  TCNT0 = 0 ;
  OCR0A = 250 - 1;
  TCCR0A |= (1<<WGM01);  //ctc mode
  TIMSK0 |= (1<<OCIE0A); //Timer/Counter0 Output Compare Match A Interrupt Enable
  TCCR0B |= (1<<CS00) | (1<<CS01);//Timer0 start 64 prescaler

}

uint32_t millis(){
  return ms;
}

ISR (TIMER0_COMPA_vect){
    ms++;
}

void UART0_AutoBaudRate(){ 
  DDRE &= ~(1<<DDE0); //porte as input
  PORTE |= (1<<PE0); //pull up on

  TCNT0 = 0; //set Counter0 register to 0
  TCCR0A = 0; //normal mode
  TCCR0B = 0; //timer0 stopped

  while ((PINE & (1<<PE0)));
  TCCR0B = (1<<CS01);  //timer0 starts; 8 prescaler
  while (!(PINE & (1<<PE0)));
  TCCR0B = 0; //timer0 stopped
  
  UBRR0 = (TCNT0>>1)-1;
}
