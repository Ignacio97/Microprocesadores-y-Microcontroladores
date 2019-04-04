#define true 1
#define false !true

#define PA 0x40 /*ports*/
#define PB 0x41
#define PC 0x42
#define RCTR 0x43 /*control register*/

/**control word**/
#define PA_AND_PB_OUT 0x89 /*Missing port is set as input*/	
#define PB_AND_PC_OUT 0x98	
#define PA_AND_PC_OUT 0x8A	
	

/*Rotate the given value to left n time, the value MUST be a byte*/
#define ROL (value,n)((value << n) | (value >> (8-n)))

typedef unsigned int word;
typedef unsigned char byte;

extern void inportb(word port);
extern byte outportb(word port,byte data);
extern void puts(char *str);
extern void putchar(char c);
extern char getch();



void  main(void) {
	byte leds ;
		leds = scan_bits();
		turnOn_leds(leds);

}


void  clrBitPort(word port,byte num_bit) {
        outportb(port, inportb(port) & ROL(0xFE,num_bit));
}

void notBitPort(word port,byte num_bit) {
        outportb(port, inportb(port) ^ (0x01 << num_bit));
}

byte testBitPort(word port,byte num_bit) {
        return !((inportb(port)&(0x01 << num_bit)) == 0);
}

void setBitPort(word port,byte num_bit) {
        outportb(port,inportb(port) | (0x01 << num_bit) );
}

byte scan_bits(void){
	byte bits,i,aux; 
 
	i = bits = 0;
	 
	outportb(RCTR,0x9B);

puts("-Captura de bits-\n\r\n\r");


	while(i++ < 8){
		puts("Bit ");
		putchar(i + '0');
		putchar(':');
		getch(); 
		aux = testBitPort(PC,4);
		bits |= (aux<<i);
		putchar(aux+'0');
		puts("\n\r");
	}

	return bits;
}

/*
-----------------------
led no|	PA | PB | PC |
-----------------------
0	  | 0  | 1  | X  |
-----------------------
1	  | 1  | 0  | X  |
-----------------------
2	  | X  | 0  | 1  |
-----------------------
3	  | X  | 1  | 0  |
-----------------------
4	  | 1  | X  | 0  |
-----------------------
5	  | 0  | X  | 1  |
-----------------------
*/
void turnOn_leds(byte bits){

	
	byte i ,bit ;

	i = bit = 0;

		while(true){

			

			if ( (bits) & (1<<bit) ){
						
				if (bit == 1 || bit == 0)				
					outportb(RCTR,PA_AND_PB_OUT);
				else if (bit == 2 || bit == 3)
					outportb(RCTR,PB_AND_PC_OUT);
				else	
					outportb(RCTR,PA_AND_PC_OUT);
					
				switch(bit){
					case 0:
					clrBitPort(PA,1);
					setBitPort(PB,1); 
					break;

					case 1: 
					clrBitPort(PB,1);
					setBitPort(PA,1); 
					break;

					case 2: 
					clrBitPort(PB,1);
					setBitPort(PC,1); 
					break;

					case 3: 
					clrBitPort(PC,1);
					setBitPort(PB,1); 
					break;

					case 4: 
					clrBitPort(PC,1);
					setBitPort(PA,1); 
					break;

					case 5: 
					clrBitPort(PA,1);
					setBitPort(PC,1); 
					break;
				}
			}

							

			bit = ++bit % 6;
			i = ++i % 3;
		}
}