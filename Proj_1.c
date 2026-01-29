#include <stdio.h>

int main() {
    int x = 0x12345678;
    unsigned char *p = (unsigned char*)&x;

    for (int i = 0; i < 4; i++)
        printf("%02x ", p[i]);
        printf("\n");
    return 0;
}
//解释执行：跨平台性强（解释器负责适配平台，代码修改少
//开发效率高
//错误可能到执行到那一行代码才发现（但这也方便了调试
//编译执行：
//开发效率较低，跨平台性较弱
//执行效率高，代码已经由编译器翻译成了机器码,CPU可直接运行
//错误在编译阶段就可以及时发现

