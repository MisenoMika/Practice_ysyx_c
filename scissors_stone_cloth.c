#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void)
{
	char gesture[3][10] = { "scissor", "stone", "cloth" };
	int man, computer, result, ret;
    bool running = true;
	srand(time(NULL));
	while (running) {
		computer = rand() % 3;
	  	printf("\nInput your gesture (0-scissor 1-stone 2-cloth):\n");
		ret = scanf("%d", &man);
        if(man == -1) {
            running = false;
            continue;
        }
	  	if (ret != 1 || man < 0 || man > 2) {
			printf("Invalid input! Please input 0, 1 or 2.\n");
			int c;
    		while ((c = getchar()) != '\n' && c != EOF){} // 清空缓冲区
			continue;
		}
		printf("Your gesture: %s\tComputer's gesture: %s\n", 
			gesture[man], gesture[computer]);

		result = (man - computer + 4) % 3 - 1;
		if (result > 0)
			printf("You win!\n");
		else if (result == 0)
			printf("Draw!\n");
		else
			printf("You lose!\n");
	}
	return 0;
}
/*scanf 的返回值是一个 int，表示 成功读取的输入项数量。

* 如果成功读取了一个整数 → 返回 1

* 如果成功读取了两个整数 → 返回 2（你这里只读一个，所以不可能）

* 如果输入不符合 %d → 返回 0

* 如果遇到文件结束（EOF） → 返回 EOF（通常是 -1）*/