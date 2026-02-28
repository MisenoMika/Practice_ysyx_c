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
	printf("%d, %d, %d, %d, %d\n",
	       arr[0], arr[1*size], arr[2*size], arr[3*size], arr[4*size]);
}

int int_cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main(void)
{
    int a[LEN] = { 10, 5, 2, 4, 7 };
	insertion_sort(a, int_cmp, sizeof(int));
	return 0;
}