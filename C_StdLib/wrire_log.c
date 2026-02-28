#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define FILENAME "test.txt"

volatile sig_atomic_t stop = 0;

/* 处理 Ctrl-C */
void handle_sigint(int sig) {
    stop = 1; // 不在handler直接exit: 延时处理,保证printf等正确执行
}

/* 读取文件最后一行的序号 */
int get_last_index(FILE *fp) {
    int last_index = 0;
    char line[256];

    rewind(fp);  // 回到文件开头

    while (fgets(line, sizeof(line), fp)) {
        int index;
        if (sscanf(line, "%d", &index) == 1) {
            last_index = index;
        }
    }

    return last_index;
}

int main() {
    signal(SIGINT, handle_sigint);

    FILE *fp = fopen(FILENAME, "a+");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    int index = get_last_index(fp);

    while (!stop) {
        index++;

        time_t now = time(NULL);
        struct tm *local = localtime(&now);

        if (!local) {
            perror("localtime");
            break;
        }

        fprintf(fp, "%d %d-%d-%d %02d:%02d:%02d\n",
                index,
                local->tm_year + 1900,
                local->tm_mon + 1,
                local->tm_mday,
                local->tm_hour,
                local->tm_min,
                local->tm_sec);

        fflush(fp);  // 立即写入磁盘

        sleep(1);
    }

    fclose(fp);
    printf("\nProgram terminated.\n");
    return 0;
}