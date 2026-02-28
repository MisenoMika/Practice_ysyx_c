#include <string.h>   // for memcpy
#include <stdio.h>
void swap(char *a, char *b, size_t size) {
    char tmp;
    for (size_t i = 0; i < size; i++) {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void qsort(void *v, int left, int right, size_t size,
           int (*comp)(const void *, const void *)) {
    int i, last;
    char *arr = v;  // 转换为 char* 方便按字节操作 *char的大小为1字节

    if (left >= right)
        return;

    swap(arr + left * size, arr + (left + right)/2 * size, size);
    last = left;

    for (i = left+1; i <= right; i++)
        if (comp(arr + i*size, arr + left*size) < 0)
            swap(arr + ++last*size, arr + i*size, size);

    swap(arr + left*size, arr + last*size, size);

    qsort(arr, left, last-1, size, comp);
    qsort(arr, last+1, right, size, comp);
}


// testbrench
int int_cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int arr[] = {3, 2, 5, 1, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    qsort(arr, 0, n-1, sizeof(int), int_cmp);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}