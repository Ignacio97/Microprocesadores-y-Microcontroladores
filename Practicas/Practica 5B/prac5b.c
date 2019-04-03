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
        outportb(port,inportb(port) | (0x1 << num_bit) );
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

void turnOn_leds(byte bits ){


		while(true){

			outportb(RCTR,PA_AND_PB_OUT); 
						


			outportb(RCTR,PB_AND_PC_OUT); 
			outportb(RCTR,PA_AND_PC_OUT); 

		}
}