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
        /***0x0 and 0xAA inverted are 0xFF and 0x55 respectively.00 and 55 are used to
           check   sticky bits; AA and 55 are used to check crosstalk bits***/

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




word addressBusTest(const word segment,const word offset,byte connected_lines){
        word totalAddress = 1,ramLoc,success=0;
        byte pattern = 0xFF;

/***totalAddress is set to 2 raised to connected_lines***/
        while (connected_lines--)
                totalAddress *= 2;

        /***set all memory to 0**/
        for (ramLoc = offset; ramLoc < offset + totalAddress; ramLoc++)
                poke(segment,ramLoc,0);

        /**write a nonzero value in the first address**/
        poke(segment,offset,pattern);
        /**search from the second position to the end for a nonzero value.**/
        for (ramLoc = offset + 1; (ramLoc < offset + totalAddress) && !success; ramLoc++) {
                success = (!peek(segment,ramLoc)) ? success : ramLoc;
        }


        /**write a nonzero value in the last address**/
        poke(segment,offset + totalAddress - 1,pattern);
        /**search from the second position to the end for a nonzero value.**/
        for (ramLoc = offset; (ramLoc < offset + totalAddress - 1) && !success; ramLoc++)
                success = (!peek(segment,ramLoc)) ? success : ramLoc;






        return success;
}
