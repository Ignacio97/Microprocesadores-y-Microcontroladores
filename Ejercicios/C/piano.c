#include <avr/interrupt.h>
#include <avr/io.h>
#include "uart.h" 


#define DO 261
#define RE 294
#define MI 329
#define FA 349
#define SOL 392
#define LA 440
#define SI 493
#define DO2 523

/**macros*/
#define ticks(f) (16000000/1024/f)

#define genFreq(freq) ({ TCCR2B=TCNT2=0;\
						 TCCR2A = 0X23;\
						 OCR2A = ticks(freq)-1;\	
						 OCR2B = ((OCR2A>>1)*90)/100;\
						 TCCR2B = (!freq) ? 0:0x0F;\ 
						}) 

/*****var****/
volatile uint16_t ms = 0;
uint16_t nota,cola[201];
uint8_t h=0,t=0; //queue,head, tail


/***funciones***/
void delay(uint16_t ms);
void record();
void play(); 
void menu();



int main(){

	 	sei();
		UART_init(0,9600,8,0,1); 
		UART0_puts("Iniciamos\n\r"); 
		
		DDRH |= (1<<PH6);  //oc2b pin
		PORTH &= ~(1<<PH6);

while(1){
		record();
		play(); 
		UART0_puts("enter para continuar\n\r");
		UART0_getch();

}

return 0; 
}



void record(){
	char c;
	
		
	clr_screen();
	UART0_puts("\n\rGrabando secuencia...\n\r");
	UART0_puts("'s' para escuhar ultmos 30s\n\r");

	do{	
		if(UART0_available()){ 		
			c = UART0_getch();
		
		switch (c){
			case '0': nota = 	DO; 
			break;
			case '1':nota = 	RE;  
			break;
			case '2': nota = 	MI; 
			break;
			case '3':nota = 	FA; 
			 break;
			case '4': nota = 	SOL; 
			break;
			case '5': nota = 	LA; 
			break;
			case '6':nota = 	SI; 
			break;
			case '7': nota = 	DO2; 
			break;	
			
			default : nota = 0; 
			break;    		
		  } 
		
		
			if(nota){
				t = ++t % 201; //wrapping tail
				cola[t] = nota;
				s
				if(h==t) h= ++h % 201; //wrapping head
				
			}
		
			genFreq(nota);
			delay(150);
		
			genFreq(0);	
		 }

		 }while(c!='s');

}



void play(){
		uint8_t bkup = h;
		char c;

	do{ 
		h=bkup;
		while( h!=t ){
			genFreq(cola[h]);
			delay(150);
			h = ++h%201;
		}
		genFreq(0);
		UART0_puts("de nuez?\n\r");
		c=UART0_getch();
	}while( c == 's'|| c=='S');	
		
		//if(h==t) t= ++t % 201; 
	h=bkup;
}




void delay(uint16_t millis){		
		
		TCNT0 = 6; //ov each 250 ticks
		TCCR0A = 0; //normal mode
		TCCR0B = 3;//1ms, prescaler 64
		TIFR0|=(1<<TOV0);

		while(millis--){

			while(!(TIFR0&(1<<TOV0)));
			
			TIFR0|=(1<<TOV0); //clear flag
		}
			

}
