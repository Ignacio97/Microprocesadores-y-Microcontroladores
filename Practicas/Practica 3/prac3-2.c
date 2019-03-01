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
        byte i,pattern,success;

        i = success = 0; /***zero means success*/

        while (i++ < 2 ) {

                pattern = (i) ? 0x55 : 0xAA;
                poke(segment,offset,pattern);
                /*****if the same pattern is read back correctly, success is set to 0 otherwise
                   success is set to the binary representation of the wrong lines.
                   Example if the line 0 and 7 are wrong then success is set to 0x81 (1000-0001).
                 ****/
                if (pattern != peek(segment, offset) ) {
                        success |= (pattern ^ peek(segment, offset));
                }
        }

        return success;
}




word addressBusTest(const word segment,const word offset,byte connected_lines){
        word totalAddress,ramLoc,success,pattern;
        byte bad_bit_found;


        totalAddress = 1;
        bad_bit_found = success = 0;
        pattern = 0x5555;

/***totalAddress is set to  2 raised to connected_lines***/
        while (connected_lines--)
                totalAddress *= 2;

        /***set all memory to 0**/
        for (ramLoc = offset; ramLoc < offset + totalAddress; ramLoc++) {
                poke(segment,ramLoc,0);
        }

        poke(segment,pattern,(byte)pattern);
        for (ramLoc = offset; ramLoc < offset + totalAddress && !bad_bit_found; ramLoc++) {
                if (peek(segment,ramLoc) == pattern && ramLoc != pattern) {
                        success |= ramLoc;
                        poke(segment,ramLoc,0);
                        bad_bit_found |= 1;
                }
        }

        /**same proccess but now using the antipattern***/
        bad_bit_found ^= bad_bit_found;
        pattern = ~pattern;
        poke(segment,pattern,(byte) pattern);
        for (ramLoc = offset; ramLoc < offset + totalAddress && !bad_bit_found; ramLoc++) {
                if (peek(segment,ramLoc) == pattern && ramLoc != pattern) {
                        success = (success & ramLoc) | ~(success ^ ramLoc);
                        bad_bit_found |= 1;
                }
        }

        return success;
}



byte deviceTest(byte connected_lines){
        long int memSize = 1;

}
