#include <stdio.h>
#include <stdbool.h>
#define MAX_ROW 5
#define MAX_COL 5
int maze[MAX_ROW][MAX_COL] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0}
};
bool visited[MAX_ROW][MAX_COL] = {false};
void print_maze(void)
{
	int i, j;
	for (i = 0; i < MAX_ROW; i++) {
		for (j = 0; j < MAX_COL; j++)
			printf("%d ", maze[i][j]);
		putchar('\n');
	}
	printf("*********\n");
}
bool dfs (int row, int col){
	if(row > MAX_ROW-1 || col > MAX_COL-1 || row < 0 || col < 0){
		return false;
	}
	
	if(maze[row][col] == 1 || visited[row][col]){
		return false;
	}

	visited[row][col] = true;

	if(row == MAX_ROW-1 && col == MAX_COL-1){
		printf("(%d, %d)\n", row, col);
		return true;
	}


	if(dfs(row+1, col) || dfs(row-1, col) || dfs(row, col+1) || dfs(row, col-1)){
		printf("(%d, %d)\n", row, col);
		return true;
	}
	return false;
}
int main(void) {
	dfs(0, 0);
	return 0;
}