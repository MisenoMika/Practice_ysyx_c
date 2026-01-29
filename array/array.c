#include <stdio.h>
#include <stdlib.h>
int get_num_from_10_to_20 (){
    return (int)rand()%11+10;
}
int main(void){
    for(int i=0; i<20; i++){
        printf("%d\n", get_num_from_10_to_20());
    }
}