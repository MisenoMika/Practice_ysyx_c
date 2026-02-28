#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
bool is_delim(char c, const char *delim) {
    return (strchr(delim, c) != NULL);
}

char *my_strtok_r(char *str, const char *delim, char **saveptr) {
    if (str != NULL) {
        *saveptr = str;

    } 
    else if (*saveptr == NULL) {
        return NULL;
    }
    else if (**saveptr == '\0') {
        *saveptr = NULL;
        return NULL;
    }


    // 跳过前置分隔符
    while (is_delim(**saveptr, delim)) {
        (*saveptr)++;
    }
    char *token = *saveptr;

    // 找到下一个分隔符
    while (**saveptr != '\0' && !is_delim(**saveptr, delim)) {
        (*saveptr)++;
    }
    if (**saveptr != '\0') {
        **saveptr = '\0';
        (*saveptr)++;
    }

    return token;
}

int main(int argc, char *argv[])
{
	char *str1, *str2, *token, *subtoken;
	char *saveptr1, *saveptr2;
	int j;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s string delim subdelim\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}

	for (j = 1, str1 = argv[1]; ; j++, str1 = NULL) {
		token = my_strtok_r(str1, argv[2], &saveptr1);
		if (token == NULL)
			break;
		printf("%d: %s\n", j, token);

		for (str2 = token; ; str2 = NULL) {
			subtoken = my_strtok_r(str2, argv[3], &saveptr2);
			if (subtoken == NULL)
				break;
			printf(" --> %s\n", subtoken);
		}
	}

	exit(EXIT_SUCCESS);
}
