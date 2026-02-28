#include <stdio.h>
#include <stdlib.h>

void test(const char *path, const char *mode) {
    FILE *fp = fopen(path, mode);
    if (fp == NULL) {
        perror(path);
    } 
    else {
        printf("Open success: %s\n", path);
        fclose(fp);
    }
}

int main() {
    test("/etc/shadow", "r");
    test("no_file.txt", "r");
    test("/home", "w");
    test("/root/test.txt", "w");
    return 0;
}