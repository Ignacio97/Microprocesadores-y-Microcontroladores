#include "timer.h"


volatile static byte SecFlag;


void interrupt ManejadorISR(void){
        static unsigned char cont = 0;

        cont++;
        if(cont==20){
        	    SecFlag = true;
        	    cont = 0;
        }
            

}

unsigned char TimerSecFlag(void){
        if(SecFlag){
        	    SecFlag = false;
        	    return true;
        }
            

        return false;
}

void Timer_Ini(void){
        SecFlag = false;
        pokew(0,INTR*4,0x100+(unsigned int)ManejadorISR);
        pokew(0,(INTR*4)+2,_CS);
}
