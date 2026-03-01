#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <src> <dst>\n", argv[0]);
        return 1;
    }

    char *buf1 = argv[1];
    char *buf2 = argv[2];
    FILE *fp1, *fp2;

    if ((fp1 = fopen(buf1, "r")) == NULL) {
        perror("Open file1");
        return 1;
    }

    if ((fp2 = fopen(buf2, "w+")) == NULL) {
        perror("Open file2");
        fclose(fp1);
        return 1;
    }

    char *line = NULL;   // getline 会分配内存
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, fp1)) != -1) {
        fputs(line, fp2);
    }


    rewind(fp2);
    while ((nread = getline(&line, &len, fp2)) != -1) {
        fputs(line, stdout);
    }

    putchar('\n');

    free(line);   // 重要：释放 getline 分配的内存
    fclose(fp1);
    fclose(fp2);
    return 0;
}