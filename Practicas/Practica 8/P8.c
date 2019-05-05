#include<avr/io.h>


#define setBitPort(port,bit) __asm__("sbi %0,%1" : :"I" ((uint8_t) (_SFR_IO_ADDR(port))) , "I" ((uint8_t) (bit)))
#define clrBitPort(port,bit) __asm__("cbi %0,%1" : :"I" ((uint8_t) (_SFR_IO_ADDR(port))) , "I" ((uint8_t) (bit)))
#define NOP() __asm__ __volatile__("nop")


#define false 0
#define true !false
#define HIGH 1
#define LOW 0

#define UNDEFINED 0
#define SHORT_PRESSED 1
#define LONG_PRESSED 2


/*Prototypes*/
void delay(uint16_t ms);
void initPorts();
uint8_t checkBtn();
void updateLeds();

uint8_t   counter  = 0;
uint32_t  millis = 0;

int main(void) {
	
	
  initPorts();
	

    while (true) {
		
      switch (checkBtn()) {

        case SHORT_PRESSED:
              counter++;
          break;

        case LONG_PRESSED:
            counter--;
          break;

      }


  		delay(1);
		millis++;
		updateLeds();
		
    }


  return 0;
}


void initPorts() {


/*
  --INTIAL OUTPUT--
  PFO : 0 (FLOATED)
  PF1 : 0 (FLOATED)
  PF2 : 0 (FLOATED)
  PF3 : 0 (FLOATED)
  PF4 : 0 (FLOATED)
  PF5 : 0 (FLOATED)
  PF6 : 0
  PF7 : 1 (PULL-UP ON)

*/
  PORTF = 0x80;

  /*
  --DATA DIRECTION--
  PFO : (FLOATED) (0)
  PF1 : (FLOATED) (0)
  PF2 : (FLOATED) (0)
  PF3 : (FLOATED)(0)
  PF4 : (FLOATED) (0)
  PF5 : FLOATED (0)
  PF6 : OUTPUT (1)
  PF7 : INPUT (0)
  */
  DDRF = 0x40;

	NOP(); //synchronization
}

void updateLeds() {
  static uint8_t led_num = 0;

  		PORTF &=  ~(1<<PF0) & ~(1<<PF1) & ~(1<<PF2) & ~(1<<PF3);
  		DDRF &= ~(1<<DDF0) & ~(1<<DDF1) & ~(1<<DDF2) & ~(1<<DDF3);
		NOP();

      if (	(counter) & (1<<led_num)){

            if (led_num == 0 || led_num ==1) {					        

                DDRF |= (1<<DDF0) | (1<<DDF1);

                if (led_num == 0) {
                    setBitPort(PORTF,PF1);					              
                } else {
                  	setBitPort(PORTF,PF0);
                }
		
				
            }
            else if (led_num == 2 || led_num == 3) {
			
              DDRF |= (1<<DDF2) | (1<<DDF1);

                if (led_num == 2) {
                  setBitPort(PORTF,PF2);
                 
                } else {
                  setBitPort(PORTF,PF1);
                }

				
            }
            else if (led_num == 4 || led_num == 5) {
			
              
              DDRF |= (1<<DDF0) | (1<<DDF2);
         

                if (led_num == 4) {
                  setBitPort(PORTF,PF0);
                } else {
                  setBitPort(PORTF,PF2);
                }

			
            }
            else if(led_num == 6|| led_num == 7){
		
           
              DDRF |= (1<<DDF3) | (1<<DDF2);
              
                if (led_num == 6) {
                  setBitPort(PORTF,PF3);
                  
                }
                else{
                  setBitPort(PORTF,PF2);                  
                }
				 
            }
			
			
    }

		
		led_num = ++led_num % 8;

  }


void delay(uint16_t ms){
  
	uint16_t x ;

	while(ms--){
		x=130;
		while(x--);	
	}

}

uint8_t checkBtn(){
	static uint32_t hit_time = 0;
	static uint8_t prev_state = HIGH;

  if ( bit_is_clear(PINF,PF7) ) {
		
		if(prev_state){
			prev_state = LOW;
			hit_time = millis;
		}

  }
  else{
  		if( (millis - hit_time) > 100 && prev_state == LOW){
				
			prev_state=HIGH;

				if((millis - hit_time) > 999){ 
				return LONG_PRESSED;
				}
				else {
				return SHORT_PRESSED;
				}
		
		}
	    
  }
	
  return UNDEFINED;
}

/***Alternative */
uint8_t checkBtn2(){

  static uint8_t prev_state = HIGH; //input pin reads 1 (PULL-UP) when no pressed
  static uint16_t ms_pressed = 0;
  uint8_t state = UNDEFINED;


  if ( bit_is_clear(PINF,PF7) ) {

      if (prev_state == HIGH) {
        delay(50);
        prev_state = LOW;
      }
      else{              //prev_state == LOW
          ms_pressed++;
      }

  }
  else{
      if (prev_state == LOW) {
      		 delay(50);

        if (ms_pressed < 999){
            state = SHORT_PRESSED;
        }
        else{
          state = LONG_PRESSED;
        }

      }
      else{
        state = UNDEFINED;
      }

      prev_state = HIGH;
      ms_pressed = 0;
  }
	

  return state;
}
