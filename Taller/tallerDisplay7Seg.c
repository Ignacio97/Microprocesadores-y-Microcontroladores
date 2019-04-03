/*********
** Padilla Ignacio
** 1246720
** 15/marzo/2019
**
***********/

#define PA 0x40
#define PB 0x41
#define PC 0x42
#define CtrlReg8255 0x43

#define PRESSED 0
#define RELEASED 1

typedef unsigned char BYTE;
typedef unsigned int WORD;

/****PROTOTIPOS*****/
void DisplayDato(BYTE n);
void display7seg();




int main(void){
								display7seg();

								return 0;
}

/**funcion principal*/
void display7seg() {
								/*******
								** sw1 es para incrementar
								** sw2 para decrementar
								***/
								BYTE num, sw1, sw2,refresh;

								num = refresh  = 0;
								sw1 = sw2 = RELEASED;
								outportb(CtrlReg8255,0x8B); //configurando 8255
								DisplayDato(num); // inicializando display

								for (;;) {

																if (sw1 == RELEASED)
																								sw1 =  getBitPort(PC,0);

																if (sw2 == RELEASED)
																								sw2 = getBitPort(PC,1);


																if (sw1 == PRESSED && getBitPort(PC,0)) {
																								if ( num < 8) {
																																num++;
																																refresh = 1;
																								}
																								sw1 = RELEASED;
																}
																if (sw2 == PRESSED && getBitPort(PC,1) ) {
																								if (num > 0) {
																																num--;
																																refresh = 1;
																								}
																								sw2 = RELEASED;
																}


																if (refresh) {
																								DisplayDato(num);
																								refresh = 0;
																}




								}
}


void DisplayDato(BYTE n){

								static BYTE display7seg[9] = { 0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0x8e};

								outportb(PA,display7seg[n]);

}
