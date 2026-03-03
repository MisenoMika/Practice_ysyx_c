#ifndef _engine_h
#define _engine_h

#include "object.h"

struct Map;
typedef struct {
    char key;
    int (*handler)(void *target);
} Command;

int execute_command(void *target, char ch, Command *commands, int command_count);
int process_input(void *target, Command *commands, int command_count);

#endif