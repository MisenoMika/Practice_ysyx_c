#include <stdio.h>
#define LEN 8
int a[LEN] = {8,7,6,5,4,3,2,1};
int count = 0;
int partition(int start, int end)
{
    int pivot = a[start];
    int i = start - 1;
    int j = end + 1;

    while (1) {
        do { i++; } while (a[i] < pivot);
        do { j--; } while (a[j] > pivot);

        if (i >= j)
            return j;

        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}


void quicksort(int start, int end)
{   
    count++;
	int mid = 0;
    printf("sort (%d-%d, %d-%d) %d %d %d %d %d %d %d %d\n", 
		       start, mid, mid+1, end, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
	if (end > start) {
		mid = partition(start, end);
		quicksort(start, mid);
		quicksort(mid+1, end);
	}
    printf("sort (%d-%d, %d-%d) %d %d %d %d %d %d %d %d\n", 
		       start, mid, mid+1, end, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
}

int main(void){
    quicksort(0, LEN-1);
    printf("%d\n", count);
    return 0;
}