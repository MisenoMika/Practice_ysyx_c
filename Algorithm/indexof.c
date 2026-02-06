#include <stdio.h>
#define LEN 8
#define INDEX 2
int a[LEN] = {8,7,6,5,4,3,2,1};
int count = 0;
int order_statistic(int start, int end)
{
    int pivot = a[start];
    int left = start;
    int right = end;
    while(left < right){
        while(a[right] >= pivot && left < right){
            right--;
        }
        a[left] = a[right];

        while (a[left] <= pivot && left < right){
            left++;
        }
        a[right] = a[left];
    }
    a[left] = pivot;
    return left;
}


int quicksort(int start, int end, int k)
{   
    count++;
	int mid = 0;
    printf("sort (%d-%d, %d-%d) %d %d %d %d %d %d %d %d\n", 
		       start, mid, mid+1, end, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
	if (end > start) {
		mid = order_statistic(start, end);
		quicksort(start, mid-1, k);
		quicksort(mid+1, end, k);
	}
    printf("sort (%d-%d, %d-%d) %d %d %d %d %d %d %d %d\n", 
		       start, mid, mid+1, end, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
    if(mid == k){
        return a[mid];
    }
    else if(mid < k){
        return a[mid - (mid - k)];
    }
    else {
        return a[mid + (k - mid)];
    }
}

int main(void){
    printf("%d\n", quicksort(0, LEN-1, INDEX-1));
    return 0;
}