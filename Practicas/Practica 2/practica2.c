extern void my_putchar(char c);
extern char my_getchar(void);
extern char my_getch(void);

void my_gets(char *str);
void my_puts(char *str);
void my_itoa(char *str, unsigned int number, unsigned char base);
unsigned int my_atoi(const char *str);

int main(void){
	
	return 0;
}


void my_gets(char *str){
	const unsigned char max_size = 10;
	const char *const aux = str + max_size - 1;
	char c;

	c = my_getchar();
	while( (c!='\n') && (str < aux) ){

		if (c == 8 && aux!=str){
            my_putchar(c);
            str--;
		}
        else{
            *(str++) = c;
        }

		c = my_getchar();
	}
	*(str) = '\0';
}

void my_puts(const char *str){
	while(*str)
		my_putchar(*(str++));
}


void my_itoa(char *str, unsigned int number, unsigned char base){
    char *str_start = str;
    char aux;

        do{
            aux = '0' + number % base;
            *(str++) = aux > '9' ? aux+7 : aux;
            number /= base;
        }while(number > 0 );

		*(str--) = '\0'; //end of str

        /***reversing the array**/

        while(str_start < str){
                aux = *str_start; //swapping contents
                *str_start = *str;
                *str = aux;
               	str_start++,str--;
        }	
}

unsigned int my_atoi(const char *str){
    unsigned int number = 0;


        while(*str){
            number += *str - '0';

            if(*(++str) ){
                number*= 10;
            }
        }

        return number;
}