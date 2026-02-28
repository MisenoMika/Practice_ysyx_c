#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *states[4] = { "California", "Oregon", "Washington", "Texas" };
    int max_states = sizeof(states) / sizeof(states[0]);
    int i = 0;

    i = 0;
    while(i < argc && i < max_states) {           
        states[i] = strdup(argv[i]);   
        i++;
    }
    
    for(i = 0; i < max_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }


    return 0;
}