extern void my_putchar(char c);
extern char my_getchar(void);
extern char my_getch(void);

void my_gets(char *str);
void my_puts(const char *str);
unsigned int my_atoi(const char *str);
void my_itoa(char *str, unsigned int number, unsigned char base);


int main(void){
        char str[20];


        unsigned int n;
        while(1) {
                my_puts("input: ");
                my_gets(str);
                my_putchar(13);
                my_putchar(10);
                n = my_atoi(str);
                my_itoa(str,n,2);
                my_puts("bin-> ");
                my_puts(str);
                my_putchar(13);
                my_putchar(10);
                my_itoa(str,n,16);
                my_puts("hex-> ");
                my_puts(str);
                my_putchar(13);
                my_putchar(10);
                my_putchar(13);
                my_putchar(10);
        }

        return 0;
}


void my_gets(char *str){

        const unsigned char max_size = 20;
        const char *const aux = str;
        char c;


        c = my_getchar();

        while( c != 13) {

                if (c != 8 ) {
                        if ( str < aux + max_size - 1 ) {
                                *(str++) = c;
                        }
                        else {
                                my_putchar(8);
                                my_putchar(32);
                                my_putchar(8);

                        }

                }
                else {
                        if (str == aux) {
                                my_putchar(32);
                        }
                        else  {
                                my_putchar(32);
                                my_putchar(c);
                                str--;
                        }
                }

                c = my_getchar();
        }

        *str = 0;

}


void my_puts(const char *str){
        while(*str)
                my_putchar(*(str++));
}


void my_itoa(char *str, unsigned int number, unsigned char base){
        char *str_start = str;
        char aux;

        do {
                aux = '0' + number % base;
                *(str++) = (aux > '9') ? aux+7 : aux;
                number /= base;
        } while(number > 0 );

        *(str--) = '\0';

        /*reversing the array*/
        while(str_start < str) {
                aux = *str_start;
                *str_start = *str;
                *str = aux;
                str_start++,str--;
        }
}

unsigned int my_atoi(const char *str){
        unsigned int number = 0;
        int aux = 0;

        while(*str) {
                aux = *str - '0';
                if (aux >=0 && aux <=9) {
                        number += aux;
                        str++;
                        if(*str >= '0' && *str <= '9') {
                                number *= 10;
                        }
                }
                else{
                        break;
                }
        }

        return number;
}
