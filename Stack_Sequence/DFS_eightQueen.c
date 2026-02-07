#include <stdio.h>
#include <stdbool.h>

#define N 8  

int solution_count = 0;

bool is_safe(int board[], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col ||                
            board[i] - i == col - row ||      
            board[i] + i == col + row) {       
            return false;
        }
    }
    return true;
}

void solve(int row, int board[]) {
    if (row == N) {
        solution_count++;
        printf("方案 %d: ", solution_count);
        for (int i = 0; i < N; i++) {
            printf("%d ", board[i]);
        }
        printf("\n");
        return;
    }

    for (int col = 0; col < N; col++) {
        if (is_safe(board, row, col)) {
            board[row] = col;   // 放置皇后（相当于入栈）
            solve(row + 1, board); // 递归到下一行
            // board[row] 不需要显式 pop，下一次循环会覆盖
        }
    }
}

int main() {
    int board[N]; // board[i] = j 表示第 i 行皇后放在第 j 列
    solve(0, board);
    printf("共 %d 种解\n", solution_count);
    return 0;
}
