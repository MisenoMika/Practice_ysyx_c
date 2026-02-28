#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>

void process(const char *file, const char *dir)
{
    FILE *fp = fopen(file, "r");
    if (!fp) return;

    char line[1024];

    while (fgets(line, sizeof(line), fp))
    {
        char name[256];

        // #include "file.h"
        if (sscanf(line, "#include \"%[^\"]\"", name) == 1)
        {
            char path[PATH_MAX];

            // 先查当前目录
            sprintf(path, "%s/%s", dir, name);
            FILE *f = fopen(path, "r");
            if (f)
            {
                fclose(f);
                char abs[PATH_MAX];
                realpath(path, abs);
                printf("%s\n", abs);

                // 递归解析
                process(abs, dir);
            }
            else
            {
                printf("%s/%s: cannot find\n", dir, name);
            }
        }
        // #include <file.h>
        else if (sscanf(line, "#include <%[^>]>", name) == 1)
        {
            char path[PATH_MAX];
            sprintf(path, "/usr/include/%s", name);
            FILE *f = fopen(path, "r");
            if (f)
            {
                fclose(f);
                char abs[PATH_MAX];
                realpath(path, abs);
                printf("%s\n", abs);
                // 系统头文件继续在 /usr/include 查
                process(abs, "/usr/include");
            }
            else
            {
                printf("/usr/include/%s: cannot find\n", name);
            }
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s file.c\n", argv[0]);
        return 1;
    }

    char abs[PATH_MAX];
    realpath(argv[1], abs);

    // 获取当前目录
    char dir[PATH_MAX];
    strcpy(dir, abs);

    char *p = strrchr(dir, '/');
    if (p) *p = '\0';

    process(abs, dir);

    return 0;
}