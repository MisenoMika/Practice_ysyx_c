#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 30
#define UPPER_BOUND 10
int a[N];
int histogram[UPPER_BOUND];

void gen_random(int upper_bound)
{
	int i;
	for (i = 0; i < N; i++)
		a[i] = rand() % upper_bound;
}

int howmany(int value)
{
	int count = 0, i;
	for (i = 0; i < N; i++){
		if (a[i] == value){
            ++count;
        }
    }
    histogram[value] = count;
	return count;
}

void printHistogram(int*b, int size){
    for(int i=0; i<size; i++){
        if(i == 0){
            for(int j=0; j<size; j++){
                printf("%d\t", j);
            }
            printf("\n");
        }
        else {
            for(int j=0; j<size; j++){
                if(histogram[j] >= i){
                    printf("*\t");
                }
                else printf(" \t");
            }
            printf("\n");
        }
    }
    printf("\n");
}
int main(void)
{
	int i;
    srand(time(NULL));
	gen_random(UPPER_BOUND);
	printf("value\thow many\n");
	for (i = 0; i < UPPER_BOUND; i++){
		printf("%d\t%d\n", i, howmany(i));
    }
    printf("\nHistogram:\n");
    printHistogram(histogram, UPPER_BOUND);
	return 0;
}