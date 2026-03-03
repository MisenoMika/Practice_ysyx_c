#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

int execute_command(void *target, char ch, Command *commands, int command_count) {   
    for(int i = 0; i < command_count; i++) {
        if(commands[i].key == ch) {
            return commands[i].handler(target);
        }
    }

    printf("Unknown command: %c\n", ch);
    return 1;
}

int process_input(void *target, Command *commands, int command_count)
{
    printf("\n> ");

    char ch = getchar();
    getchar(); // eat ENTER

    return execute_command(target, ch, commands, command_count);
}