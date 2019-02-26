extern void poke(unsigned int segment, unsigned int offset, unsigned char data);
extern unsigned char peek(unsigned int segment, unsigned int offset);

typedef unsigned char byte;
typedef unsigned int word;

int main(void) { return 0; }

/***************************
**  Function : dataBusTest()
**
**
**
**
**
**
** Returns : 0 if the test succeeds,
**            otherwise the first failed pattern.
**
**
***************************/
byte dataBusTest(const word segment, const word offset) {
  byte pattern, success = 0;

  for (pattern = 0x01; pattern && !success; pattern <<= 1) {
    poke(segment, offset, pattern);

    success = (pattern == peek(segment, offset)) success : pattern;
  }

  return success;
}
