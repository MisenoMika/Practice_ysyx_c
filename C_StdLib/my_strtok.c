#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_delim(char c, const char *delim) {
    return (strchr(delim, c) != NULL);
}

char *my_strtok(char *src, char *delim) {
    static char *saveptr;
    if(src != NULL) {
        saveptr = src;
    } else if(saveptr == NULL) {
       return NULL; 
    } else if(*saveptr == '\0') {
        saveptr = NULL;
        return NULL;
    }

    while(is_delim(*saveptr, delim)) {
        saveptr++;
    }

    char *token = saveptr;
    while (*saveptr != '\0' && !is_delim(*saveptr, delim)) {
        saveptr++;
    }

    if(*saveptr != '\0') {
        *saveptr = '\0';
        saveptr++;
    }
    return token;
    
    
}

int main(void)
{
	char str[] = "root:x::0:root:/root:/bin/bash:";
	char *token;

	token = my_strtok(str, ":");
	printf("%s\n", token);
	while ( (token = my_strtok(NULL, ":")) != NULL)
		printf("%s\n", token);
	
	return 0;
}