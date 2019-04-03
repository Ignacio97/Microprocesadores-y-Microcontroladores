#define true 1
#define false 0
#define INTR 8
#define MAPPED_PORT 0xffff

#define enter() putchar('\n'),putchar('\r')


typedef unsigned int word;
typedef unsigned char byte;

byte TimerSecFlag(void);
void Timer_Ini(void);

extern void pokew(word seg,word offset, word value);
extern void poke(word seg,word offset, byte value);
extern void putchar(byte c);
