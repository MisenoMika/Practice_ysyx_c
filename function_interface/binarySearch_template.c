#include <stdio.h>
#include <stddef.h>
#define LEN 8

int binarysearch(int number, void*arr_in, int(*cmp)(const void*, const void*), size_t size)
{
	int mid, start = 0, end = LEN - 1;
    char *a = arr_in;
	while (start <= end) {
        mid = (start + end) / 2;
        int r = cmp(&number, a + mid*size);
        if (r > 0)
            start = mid + 1;
        else if (r < 0)
            end = mid - 1;
        else
            return mid;
    }
	return -1;
}

int int_cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main(void)
{
    int a[LEN] = { 1, 2, 2, 2, 5, 6, 8, 9 };
    int dest = binarysearch(5, a, int_cmp, sizeof(int));
	printf("%d\n", dest);
	return 0;
}