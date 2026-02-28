#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *buf1 = argv[1];
    char *buf2 = argv[2];
    FILE *fp1, *fp2;
    int ch;
    if ( (fp2 = fopen(buf2, "w+")) == NULL) {
		perror("Open file file2\n");
		exit(1);
	}
    if ( (fp1 = fopen(buf1, "r")) == NULL) {
		perror("Open file file1\n");
		exit(1);
	}

    while( (ch = fgetc(fp1)) != EOF) {
        fputc(ch, fp2);
    }
    rewind(fp2);
    while((ch = fgetc(fp2)) != EOF) {
        putchar(ch);
    }
    putchar('\n');
    fclose(fp1);
    fclose(fp2);
    return 0;
}