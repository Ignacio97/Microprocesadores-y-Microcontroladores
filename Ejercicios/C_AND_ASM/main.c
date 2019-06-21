#include <inttypes.h>

extern uint32_t inc_2(uint32_t x); 

int main(){
	uint32_t value = 0xfffffff0;

	while(1){
		value = inc_2(value);
	}


return 0;
}
