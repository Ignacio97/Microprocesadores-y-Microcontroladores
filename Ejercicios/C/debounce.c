
/** Realizar un programa que encienda un led solo cuando se presione un boton. 
	PF0 : catodo del led
	PF1 : anodo
	PF2 : botton en pull up
**/

#include <avr/io.h>
#include <avr/interrupt.h>


/*inicia puertos**/
void initPort();

/*prende el led**/
void turnOn();

/*apaga el led*/
void turnOff();

/*devuelve 1 si el led esta presionado,
caso contrario 0*/
uint8_t btnStatus();

/********/
void delay_20ms();



int main(){
	
	cli();
	initPort();

	while(1){
			
			if(btnStatus())
				turnOn();
			else
				turnOff();
	}

	
	return 0; 

}


void initPort(){
	DDRF = (1<<DDF0) | (1<< DDF1);
	DDRF &=  ~(1<<DDF2);
	PORTF = (1<<PF2); //pull up on  
}

void turnOn(){
	PORTF |= (1<<PF1); 
}
void turnOff(){
		PORTF &= ~(1<<PF1); 
}

uint8_t btnStatus(){
	
	if(!(PINF&1<<PF2)){
		
		delay_20ms();
		
		if(!(PINF&(1<<PF2))){	
			return 1; 
		}
	}

	return 0; 


}

void delay_20ms(){
	
	TIFR0 |= 1<<TOV0 ; //borrar bandera ov
	TCCR0A = 0; //NORMAL MODE
	TCNT0 = 0XFF + 1 - 156; // 10MS 
	TCCR0B = (5<<CS00); //PRESCALER TO 1024 

	for(uint8_t i = 0; i<2;i++){  //2 * 10 = 20ms
		while (!(TIFR0&(1<<TOV0))); 
	 	TIFR0 |= 1<<TOV0 ;	
	 }
	TCCR0B = 0; //timer off

}
