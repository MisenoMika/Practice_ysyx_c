#include <stdio.h>
#include <stdbool.h>

#define N 8

int solution_count = 0;

bool is_safe(int board[], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col ||                 // 同列
            board[i] - i == col - row ||       // 主对角线
            board[i] + i == col + row) {       // 副对角线
            return false;
        }
    }
    return true;
}

void print_board(int board[]) {
    printf("方案 %d:\n", ++solution_count);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void solve(int row, int board[]) {
    if (row == N) {
        print_board(board);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (is_safe(board, row, col)) {
            board[row] = col;      // 入栈：在第 row 行放皇后
            solve(row + 1, board); // 深度优先
            // 出栈：隐式完成，board[row] 会被下一次覆盖
        }
    }
}

int main() {
    int board[N];
    solve(0, board);
    printf("总解数：%d\n", solution_count);
    return 0;
}
