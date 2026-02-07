#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int N, M;

int* nums;
int* nums_index;
void dfs(int start, int depth){
    if(depth == M){
        for(int i=0; i<depth; i++){
            printf("%d  ", nums[nums_index[i]]);
        }
        printf("\n");
    }
    else {
        for(int i= start; i<N; i++){ // 隐式剪枝（implicit pruning）
            nums_index[depth] = i; // 当for循环不成立的时候跳过for循环,然后返回
            dfs(i+1, depth+1);
        }
    }
}

int main(void){
    N = 3;
    M = 2;
    nums = malloc(N * sizeof *nums);
    if (!nums)
        goto out;

    nums_index = malloc(M * sizeof *nums_index);
    if (!nums_index)
        goto free_nums;

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        nums[i] = rand() % 30;
        nums_index[i] = i;
        printf("%d  ", nums[i]);
    }
    printf("\n");
    dfs(0, 0);

free_nums_index:
    free(nums_index);
free_nums:
    free(nums);
out:
    return 0;
}
