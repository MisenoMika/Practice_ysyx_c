#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int *ptr = NULL;  // 空指针

    while (i < 10) {
        usleep(3000); // 睡 3ms
        i++;
    }

    // 故意崩溃：解引用空指针
    *ptr = 42;

    return 0;
}