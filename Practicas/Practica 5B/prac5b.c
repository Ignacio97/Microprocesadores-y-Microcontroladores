#define true 1
#define false !true

#define PA 0x40 /*ports*/
#define PB 0x41
#define PC 0x42
#define RCTR 0x43 /*control register*/

/**control word**/
#define PA_AND_PB_OUT 0x89 /*Missing port is set as input*/
#define PB_AND_PC_OUT 0x90
#define PA_AND_PC_OUT 0x82

/*Rotate the given value to left n time, the value MUST be a byte*/
#define ROL(value,n)((value << n) | (value >> (8-n)))

#define SET_LED_ON(A,C) do { \
                            setBitPort(A,1); \
                            clrBitPort(C,1); \
                        }while(0)

typedef unsigned int word;
typedef unsigned char byte;

extern byte inportb(word port);
extern void outportb(word port, byte data);
extern void putchar(char c);
extern char getch();
void clrBitPort(word port, byte num_bit);
void notBitPort(word port, byte num_bit);
byte testBitPort(word port, byte num_bit);
void setBitPort(word port, byte num_bit);
byte scan_bits();
void delay(byte a);
void turnOn_leds(byte l);

void main( void ){
    byte k;
    k = scan_bits();

    while(true){
        turnOn_leds(k);
    }
}

void puts(char *str){
    while(*str){
        putchar(*(str++));
    }
}

void clrBitPort(word port, byte num_bit){
    outportb(port, inportb(port) & ROL(0xFE,num_bit));
}

void notBitPort(word port, byte num_bit){
    outportb(port, inportb(port) ^ (0x01 << num_bit));
}

byte testBitPort(word port, byte num_bit){
    return !((inportb(port)&(0x01 << num_bit)) == 0);
}

void setBitPort(word port, byte num_bit){
    outportb(port, inportb(port) | (0x01 << num_bit));
}

byte scan_bits(void){
    byte bits, i, aux;
    i = bits = 0;
    outportb(RCTR,0x9B);
    puts("Captura de bits\n\r\n\r");

    while(i < 8){
        puts("Bit ");
        putchar(i + '0');
        putchar(':');
        getch();
        aux = testBitPort(PC,4);
        bits |= (aux<<i);
        putchar(aux+'0');
        puts("\n\r");
        i++;
    }
    return bits;
}

void delay(byte a){
    while(a--);
}

void turnOn_leds(byte l){
    byte j,aux;
    j=0;

    while(true){
        aux = l&(1<<j);
        if(aux){
            if(j==0 || j==1){
                outportb(RCTR,PA_AND_PB_OUT);
                if(j==0)
                    SET_LED_ON(PB,PA);
                else
                    SET_LED_ON(PA,PB);
            }
            else if(j==2 || j==3){
                outportb(RCTR,PB_AND_PC_OUT);
                if(j==2)
                    SET_LED_ON(PC,PB);
                else
                    SET_LED_ON(PB,PC);
            }
            else{
                outportb(RCTR,PA_AND_PC_OUT);
                if(j==4)
                    SET_LED_ON(PA,PC);
                else
                    SET_LED_ON(PC,PA);
            }
            delay(20);
        }
        j = ++j % 6;
    }
    
}