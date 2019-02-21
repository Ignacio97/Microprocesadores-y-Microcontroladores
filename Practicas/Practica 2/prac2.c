
extern void my_putchar(char c);
extern char my_getchar(void);
extern char my_getch(void);

void my_gets(char *str);
void my_puts(const char *str);
unsigned int my_atoi(const char *str);
void my_itoa(char *str, unsigned int number, unsigned char base);


int main(void){
        char str[50];
        int n;

        while(1) {
                my_puts("input: ");
                my_gets(str);
                n = my_atoi(str);
                my_itoa(str,n,2);
                my_puts("bin-> ");
                my_puts(str);
                my_putchar('\n');
                my_itoa(str,n,16);
                my_puts("hex-> ");
                my_puts(str);
                my_putchar('\n');
                my_putchar('\n');
        }




        return 0;
}


void my_gets(char *str){

        const unsigned char max_size = 50;
        const char *const aux = str;
        char c;

        c = my_getchar();

        while( (c != 13) && (str < aux + max_size - 1)) {

                if (c == 8) { /*if c is backspace*/
                        if (str != aux) { /*does the str has something stored?*/
                                my_putchar(32); /*white space ascii*/
                                my_putchar(c); /*if the program has reached here c must be backspace!!*/
                                str--; /*decrease str*/
                        }
                        else{
                                my_putchar(32); /*white space ascii*/
                        }
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
