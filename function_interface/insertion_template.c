#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define LEN 5


void insertion_sort(void* arr_in, int (*comp)(const void *, const void *), size_t size)
{
	int j;
    char* arr = (char*)arr_in;
    char key[size];

    for (j = 1; j < LEN; j++) {
        memcpy(key, arr + j*size, size);
        int i = j - 1;

        while (i >= 0 && comp(arr + i * size, key) > 0) {
            memmove(arr + (i + 1)*size, arr + i*size, size);
            i--;
        }
        memcpy(arr + (i + 1) * size, key, size);
    }
}

int int_cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}
int double_cmp(const void *a, const void *b) {
    double diff = *(double*)a - *(double*)b;
    if (diff < 0) return -1;
    else if (diff > 0) return 1;
    else return 0;
}
int main(void)
{
    int a[LEN] = { 10, 5, 2, 4, 7 };
	insertion_sort(a, int_cmp, sizeof(int));
    printf("%d, %d, %d, %d, %d\n", a[0], a[1], a[2], a[3], a[4]);
    double b[LEN] = { 3.14, 2.71, 1.41, 1.73, 0.577 };
    insertion_sort(b, double_cmp, sizeof(double));
    printf("%.3f, %.3f, %.3f, %.3f, %.3f\n", b[0], b[1], b[2], b[3], b[4]);
	return 0;
}