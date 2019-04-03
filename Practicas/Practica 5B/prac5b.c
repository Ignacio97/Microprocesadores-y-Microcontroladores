

#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCTR 0x43
/**control word**/


/*Rotate a byte to left n time*/
#define ROL (value,n)((value << n) | (value >> (8-n)))


typedef unsigned int word;
typedef unsigned char byte;

extern void inportb(word port);
extern byte outportb(word port,byte data);

void  main(void) {



}


void  clrBitPort(word port,byte num_bit) {
        outportb(port, inportb(port) & ROL(0xFE,num_bit));
}

void notBitPort(word port,byte num_bit) {
        outportb(port, inportb(port) ^ (0x01 << num_bit));
}

byte testBitPort(word port,byte num_bit) {
        return ( inportb(port) & (0x01 << num_bit) );
}

void setBitPort(word port,byte num_bit) {
        outportb(port,inportb(port) | (0x1 << num_bit) );
}
