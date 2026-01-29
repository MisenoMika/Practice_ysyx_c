#include <iostream>
using namespace std;

// 交换函数
void swap(int &a, int &b) { int t = a; a = b; b = t; }

// 打印数组
void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// 全排列递归函数
void permute(int arr[], int start, int n) {
    if(start == n) {        // 所有位置都固定好了，打印
        printArray(arr, n);
        return;
    }

    for(int i = start; i < n; i++) {
        swap(arr[start], arr[i]);   // 把第i个数换到当前位置
        permute(arr, start + 1, n); // 对剩下的数做全排列
        swap(arr[start], arr[i]);   // 回溯
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    permute(arr, 0, n);  // 从第0个位置开始排列
    return 0;
}
