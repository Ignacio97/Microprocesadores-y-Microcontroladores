extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
extern unsigned char peek(unsigned int segment, unsigned int offset);

typedef unsigned char byte;
typedef unsigned int word;

int main(void) {
        return 0;
}

/***************************
**  Function : dataBusTest()
**
**  Check a 8 bits data bus in the given address specified
**  by the segment and offset.
**
**
**
**
** Returns : 0 if the test succeeds,
**
**
**
***************************/
byte dataBusTest(const word segment,const word offset) {
        byte i,j,pattern,success;
        const byte tests[] = {0x0,0xAA};

        i = j = success = 0; /***zero means success*/

        while (i++ < 2 && !success) {
                while(j++ < 2 && !success) {
                        pattern = (j) ? ~tests[i] : tests[i];
                        poke(segment,offset,pattern);
                        /*****if the same pattern is read back correctly, success is set to 0 otherwise
                           success is set to the binary representation of the wrong lines.
                           Example if the line 0 and 7 are wrong then success is set to 0x81 (1000-0001).
                         ****/
                        success = (pattern == peek(segment, offset)) success:pattern ^ peek(segment, offset);
                }
        }

        return success;
}




word addressBusTest(const word segment,const word offset,byte bus_lines){
        word pattern, success = 0;


        return success;
}
