#include <stdio.h>
#define LEN 8
int a[LEN] = {8,7,6,5,4,3,2,1};
int count = 0;
int partition(int start, int end)
{
    int pivot = a[start];
    int i = start;

    for (int j = start + 1; j <= end; j++) {
        if (a[j] < pivot) {
            i++;
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
    a[start] = a[i];
    a[i] = pivot;
    return i;
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
		quicksort(start, mid-1);
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