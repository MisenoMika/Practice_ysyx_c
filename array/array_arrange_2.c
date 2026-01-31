#include <stdio.h>

int N, M;
int path[100];

void dfs(int start, int depth)
{
    // 终止条件：已经选了 M 个
    if (depth == M) {
        for (int i = 0; i < M; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return;
    }

    // 从 start 开始选
    for (int i = start; i <= N; i++) {
        path[depth] = i;
        dfs(i + 1, depth + 1);  // 只能选后面的数
    }
}

int main(void)
{
    N = 5;
    M = 3;
    dfs(1, 0);
    return 0;
}
