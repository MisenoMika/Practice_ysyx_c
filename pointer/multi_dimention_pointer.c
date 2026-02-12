#include <stdio.h>
int main(void) {
    char a[4][3][2] = {
        {{'a', 'b'}, {'c', 'd'}, {'e', 'f'}},
		{{'g', 'h'}, {'i', 'j'}, {'k', 'l'}},
		{{'m', 'n'}, {'o', 'p'}, {'q', 'r'}},
		{{'s', 't'}, {'u', 'v'}, {'w', 'x'}}
    };

    char (*pa)[2] = &a[1][0];
    char (*ppa)[3][2] = &a[1];
    pa = pa + 5;
    char alpha = (*pa)[1];
    ppa++;
    char beta = (*ppa)[2][1];
    printf("%c\n", a[2][2][1]);
    printf("%c\n", alpha);
    printf("%c\n", beta);
    ppa -= 2;
    printf("%c\n", (*ppa)[2][1]);
}