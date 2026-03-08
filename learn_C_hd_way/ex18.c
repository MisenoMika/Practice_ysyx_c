#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
/** Our old friend die from ex17. */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b);

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    assert(numbers != NULL && "numbers being sorted are NULL");
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    for(i = 0; i < count; i++) {
        for(j = 0; j < count - 1; j++) {
            if(cmp(target[j], target[j+1]) > 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

void merge(int a[], int start, int mid, int end, compare_cb cmp)
{
	int n1 = mid - start + 1;
	int n2 = end - mid;
	int left[n1], right[n2];
	int i, j, k;

	for (i = 0; i < n1; i++) /* left holds a[start..mid] */
		left[i] = a[start+i];
	for (j = 0; j < n2; j++) /* right holds a[mid+1..end] */
		right[j] = a[mid+1+j];

	i = j = 0;
	k = start;
	while (i < n1 && j < n2)
		if (cmp(left[i], right[j]) < 0)
			a[k++] = left[i++];
		else
			a[k++] = right[j++];

	while (i < n1) /* left[] is not exhausted */
		a[k++] = left[i++];
	while (j < n2) /* right[] is not exhausted */
		a[k++] = right[j++];
}

void merge_sort(int a[], int start, int end, compare_cb cmp)
{
    int mid;
    if (start < end) {
        mid = (start + end) / 2;
        merge_sort(a, start, mid, cmp);
        merge_sort(a, mid+1, end, cmp);
        merge(a, start, mid, end, cmp);
    }
}

int *merge_sort_wrapper(int *numbers, int count, compare_cb cmp)
{
    int *target = malloc(count * sizeof(int));
    if(!target) die("Memory error.");

    memcpy(target, numbers, count * sizeof(int));

    merge_sort(target, 0, count - 1, cmp);

    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}
    // this is going to be a big function so I won't write it here
/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, int *(*sort_func)(int *, int, compare_cb), compare_cb cmp)
{
    int i = 0;

    int *sorted = sort_func(numbers, count, cmp);

    if(!sorted) die("Failed to sort.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }

    printf("\n");

    free(sorted);
}

int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, bubble_sort, sorted_order);
    test_sorting(numbers, count, merge_sort_wrapper, sorted_order);
    printf("\nreverse_order: \n");
    test_sorting(numbers, count, bubble_sort, reverse_order);
    test_sorting(numbers, count, merge_sort_wrapper, reverse_order);
    free(numbers);
    numbers = NULL;
    test_sorting(numbers, count, bubble_sort, reverse_order);
    return 0;
}