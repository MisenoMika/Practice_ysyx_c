#include <stdio.h>
#include <stdarg.h>
#include <string.h>
char *my_strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while ((*dest++ = *src++));
    return tmp;
}
void int_to_char(char *output, int input) {
    char buf[32];
    int n = 0;
    unsigned int nums = input;
    if(input == 0) {
        output[0] = '0';
        output[1] = '\0';
        return;
    }
    if (input < 0) {
        nums = -input;
    } 
    while (nums != 0) {
        int digit = nums % 10;
        buf[n++] = (char)('0' + digit);
        nums /= 10;
    };
    if (input < 0) {
        buf[n++] = '-';
    }

    for (int i = 0; i < n; ++i) {
        output[i] = buf[n - 1 - i];
    }
    output[n] = '\0';
}

int int_to_char_for_float(char *output, int input) {
    char buf[32];
    int n = 0;
    unsigned int nums = input;
    if(input == 0) {
        output[0] = '0';
        output[1] = '\0';
        return 1;
    }
    if (input < 0) {
        nums = -input;
    } 
    while (nums != 0) {
        int digit = nums % 10;
        buf[n++] = (char)('0' + digit);
        nums /= 10;
    };
    if (input < 0) {
        buf[n++] = '-';
    }
    for (int i = 0; i < n; ++i) {
        output[i] = buf[n - 1 - i];
    }
    return n;
}

void float_to_char(char* output, double input) {
    char buf_1[32];
    char buf_2[32];
    if(input == 0) {
        output[0] = '0';
        output[1] = '\0';
        return;
    }

    input = (input < 0)? -input : input;
    
    int tmp = (int)input;
    int len = int_to_char_for_float(buf_1, tmp);
    buf_1[len] = '.';
    int digit = 1;
    input -= tmp;

    int len_after_point = 3;
    for(int i=0; i<len_after_point; i++) {
        input *= 10;
        digit = (int)input%10;
        buf_2[i] = (char)('0'+digit);
    }

    for(int i=0; i<len+1; i++) {
        output[i] = buf_1[i];
    }
    for(int i = 0; i < len_after_point; i++) {
        output[i + 1 +len] = buf_2[i];
    }
    output[len + len_after_point + 1] = '\0';
}
void myprintf(const char *format, ...)
{
     va_list ap;
     char c;

     va_start(ap, format);
     while ((c = *format++) != '\0') {
        if(c == '%'){
            c = *format++;
            switch(c) {
            case 'c': {
                /* char is promoted to int when passed through '...' */
                char ch = va_arg(ap, int);
                putchar(ch);
                break;
            }
            case 's': {
                char *p = va_arg(ap, char *);
                fputs(p, stdout);
                break;
            }
            case 'd':{
                int p = va_arg(ap, int);
                char dest[33];
                int_to_char(dest, p);
                fputs(dest, stdout);
                break;
            }
            case 'f':{
                double p = va_arg(ap, double);
                char dest[64];
                float_to_char(dest, p);
                fputs(dest, stdout);
                break;
            }
            default:
                putchar(c);
            }
        }
        else putchar(c);
     }
     va_end(ap);
}

int main(void)
{
     myprintf("%c\t%s\t%d\t%f\n", '1', "hello", -200, -1.145);
     return 0;
}