
/***************************
**  Author : Chavez Padilla Ignacio
**  Date : 01/march/2019
***************************/


/***************************
**  Function : Poke()
**
**  Writes the given byte into memory at the
**  specified segment and offset.
***************************/
extern void poke(unsigned int segment, unsigned int offset, unsigned char data);

/***************************
**  Function : peek()
**
**  Reads a byte from memory at the
**  specified segment and offset.
**
**  Returns: The byte read from memory.
***************************/
extern unsigned char peek(unsigned int segment, unsigned int offset);

extern void my_putchar(char c);
extern char my_getchar(void);
extern char my_getch(void);

typedef unsigned char byte;
typedef unsigned int word;

/***********PROTOTYPES********/
void my_puts(const char *str);
byte dataBusTest(const word segment,const word offset);
word addressBusTest(const word segment,const word offset,byte connected_lines);
void dataBusStatus(byte status);
void addresBusStatus(word status,byte lines);
void enter();
/***********PROTOTYPES********/



int main(void) {

        for(;;) {
                dataBusStatus(dataBusTest(0,0x2200));
                addresBusStatus(addressBusTest(0,0x2800,11),11);
                my_getch();
        }

        return 0;
}

/***************************
**  Function : dataBusTest()
**
**  Check a 8 bits data bus in the given specified
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


word addressBusTest(const word segment,const word offset,byte connected_lines){
        word success,ramLoc,pattern;

        pattern = 0xAAAA;
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
