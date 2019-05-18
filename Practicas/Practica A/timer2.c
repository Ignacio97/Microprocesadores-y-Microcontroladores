#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>

static  uint8_t Flag = 0;


void Timer2_Ini( uint8_t baseT ){

/* Configurar Timer2 para usar cristal externo según */
/* secuencia dada por la hoja de especificaciones */

	TIMSK2 = 0; //clear timer2 Int
	ASSR =  (1<<AS2); 
	
	TCCR2A = (1<<WGM21); //mode ctc
	TCCR2B = (1<<CS20)|(1<<CS21)|(1<<CS22); //1024 prescaler

	TCNT2 = 0;
	
/** 1- Tclk = 1/Ftimer */
/** 2- n = desireTime / Tclk  */
/** 3- OCRxA = n - 1 */

	OCR2A = baseT<<5; //ocra = desire time /(1/32) = desire time * 32 
	
	while((ASSR & (1<<TCN2UB)) || (ASSR & (1<<OCR2AUB))||(ASSR & (1<<TCR2AUB)));
	

	TIFR2 = 0;
	TIMSK2 = 0x02;
	sei();

}

uint8_t Timer2_Flag( void ){
  
        if(Flag) {
                Flag = 0;
               return 1;
        }

        return 0;
}

/* Rutina de Servicio de Interrupción para atender la interrupción */
/* por Comparación del Timer2 (TCNT2 y OCR2 son iguales) */
ISR(TIMER2_COMPA_vect){
        Flag = 1; /* Activa Bandera para indicar los 1 segundos */
} /* fin de la rutina de servicio de Interrupción (RSI) */
