#include <stdio.h>
#include <stddef.h>
enum STATE {NORMAL, REMOVE};
char *my_strcpy(char *dest, const char *src);
char *shrink_space(char *dest, const char *src, size_t n);
int main(void) {
    char *ch = "SUAT";
    char dest[10];
    my_strcpy(dest, ch);
    printf("%s\n", dest);
    for(int i=0; i<10; i++) {
        printf("%c  ", dest[i]);
    }
    printf("\n");
    char *src =
        "This Content hoho       is ok\n"
        "            ok?\n"
        "\n"
        "            file system\n"
        "    uttered words   ok ok      ?\n"
        "    end.";
    char dest2[500];
    shrink_space(dest2, src, 120);
    printf("%s\n", dest2);
}

char *my_strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while ((*dest++ = *src++));
    return tmp;
}

char *shrink_space(char *dest, const char *src, size_t n) {
    size_t i = 0;
    int state = NORMAL, nextstate = NORMAL;
    char *tmp = dest;
    for(; i<n; i++) {
        state = nextstate;
        if(*src == ' ' || *src == '\n'){
            nextstate = REMOVE;
            if(state == NORMAL && nextstate == REMOVE) {
                *dest++ = ' ';
            }
            src++;
            continue;
        } 
        else {
            *dest++ = *src++;
            nextstate = NORMAL;
        }
    }
    *dest = '\0';
    return tmp;

}