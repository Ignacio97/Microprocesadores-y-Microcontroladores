
/***************************
**  Author : Chavez Padilla Ignacio
**  Date : 08/march/2019
***************************/


typedef unsigned char byte;
typedef unsigned int word;

/***************************
**  Function : Poke()
**
**  Writes the given byte into memory at the
**  specified segment and offset.
***************************/
extern void poke(word segment,word offset, byte data);

/***************************
**  Function : peek()
**
**  Reads a byte from memory at the
**  specified segment and offset.
**
**  Returns: The byte read from memory.
***************************/
extern unsigned char peek(word segment, word offset);


extern void my_putchar(char c);
extern char my_getchar(void);
extern char my_getch(void);


/***********PROTOTYPES********/
void my_puts(const char *str);
byte dataBusTest(const word segment,const word offset);
word addressBusTest(const word segment,const word offset,byte connected_lines);
void dataBusStatus(byte status);
void addresBusStatus(word status,byte lines);
void enter();
/***********PROTOTYPES********/

const word SEG =0; /*segment*/
const byte LIN = 11;  /*lines*/


int main(void) {

        for(;;) {
                my_puts("ADDRESS 5800h(inicio)\n\r");
                dataBusStatus(dataBusTest(SEG,0x5800));
                addresBusStatus(addressBusTest(SEG,0x5800,LIN),LIN);
                my_getch();

                my_puts("ADDRESS 7800h(espejo)\n\r");
                dataBusStatus(dataBusTest(SEG,0x7800));
                addresBusStatus(addressBusTest(SEG,0x7800,LIN),LIN);
                my_getch();

                my_puts("ADDRESS 5000h\n\r");
                dataBusStatus(dataBusTest(SEG,0x5000));
                addresBusStatus(addressBusTest(SEG,0x5000,LIN),LIN);
                my_getch();

                my_puts("ADDRESS 7000h\n\r");
                dataBusStatus(dataBusTest(SEG,0x7000));
                addresBusStatus(addressBusTest(SEG,0x7000,LIN),LIN);
                my_getch();

        }

        return 0;
}

/***************************
**  Function : dataBusTest()
**
**  Checks a 8 bits data bus in the given address specified
**  by the segment and offset.
**
** Returns : 0 if the test succeeds,otherwise
**  a binary pattern representation of the wrong lines.
**    Example: If 0x80 is returned means bit 7 is not working.
**
***************************/
byte dataBusTest(const word segment,const word offset) {
        byte pattern,success;

        success = 0; /***zero means success*/

        for ( pattern = 1; pattern; pattern<<=1) {
                poke(segment,offset,pattern);
                if ( peek(segment,offset) != pattern) {
                        success |= pattern;
                }
        }
        return success;
}

/***************************
**  Function : addressBusTest()
**
**  Param:
**  connected_lines : Lines connected to memory.
**
** Returns : 0 if the test succeeds,otherwise
**  a binary pattern representation of the wrong lines.
**    Example: If 0x0080 is returned means bit 7 is not working.
**
** Note:connected_lines must be a number above than zero and below or equal to sixteen.
***************************/
word addressBusTest(const word segment,const word offset,byte connected_lines){
        word success,ramLoc;
        byte pattern;

        pattern = 0xAA;
        success = 0;

        /**filling each power of two address to zero*/
        for (ramLoc = 1; ramLoc < (1<<connected_lines); ramLoc<<=1) {
                poke(segment,offset + ramLoc,success);
        }

        /*write a known pattern */
        poke(segment,offset,pattern);

        for (ramLoc = 1; ramLoc < (1<<connected_lines); ramLoc<<=1) {
                if (peek(segment,offset + ramLoc) == pattern || peek(segment,offset + ramLoc) != 0 ) {
                        success |=ramLoc;
                }
        }
        return success;
}



void dataBusStatus(byte status){
        byte i = 0;

        my_puts("-----------DATA BUS TEST---------");
        enter();


        while (i < 8) {
                my_puts("LINE ");
                my_putchar( i + '0' );
                my_puts(":");
                if (status & (0x01 << i))
                        my_puts("[ERRROR]");
                else
                        my_puts("[OK]");

                i++;
                enter();
        }

        enter();

}

void addresBusStatus(word status,byte lines) {
        word i = 0;

        my_puts("---------------ADDRESS BUS TEST-------------");
        enter();

        while (i < lines) {

                my_puts("LINE ");
                my_putchar( (i > 9) ? i+'0'+7 : i+'0'  );
                my_puts(":");

                if (status & (0x0001 << i))
                        my_puts("[ERROR]");
                else
                        my_puts("[OK]");

                enter();
                i++;
        }

        enter();
}

void my_puts(const char *str){
        while(*str)
                my_putchar(*(str++));
}

void enter(){
        my_putchar(13);
        my_putchar(10);
}
