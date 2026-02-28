#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LINE_SIZE 1024

char *trim(char *s) {
    while (isspace((unsigned char)*s)) s++;
    if (*s == '\0') return s;

    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) end--;
    *(end+1) = '\0';

    return s;
}

void print_comment(const char *s) {
    printf("<!-- %s -->\n", s + 1);
}

void print_section_start(const char *name) {
    printf("<%s>\n", name);
}

void print_section_end(const char *name) {
    printf("</%s>\n\n", name);
}

void print_kv(const char *key, const char *value) {
    printf("\t<%s>%s</%s>\n", key, value, key);
}

void convert_ini_to_xml(FILE *in) {
    char line[LINE_SIZE];
    char current_section[256] = "";
    int has_section = 0;

    while (fgets(line, sizeof(line), in))
    {
        if (*line == '\0') {
            continue;
        }
        if (*line == ';') {
            print_comment(line);
            continue;
        }

        if (*line == '[') {
            char *end = strchr(line, ']');
            if (!end) continue;

            *end = '\0';

            if (has_section) {
                print_section_end(current_section);
            }
            strcpy(current_section, line + 1);
            print_section_start(current_section);

            has_section = 1;
            continue;
        }

        char *eq = strchr(line, '=');
        if (eq)
        {
            char *key = trim(line);
            char *value = trim(eq + 1);

            print_kv(key, value);
        }
    }

    if (has_section)
        print_section_end(current_section);
}

int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <ini_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen");
        return EXIT_FAILURE;
    }

    convert_ini_to_xml(fp);

    fclose(fp);
    return EXIT_SUCCESS;
}