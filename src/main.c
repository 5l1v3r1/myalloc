#include <stdio.h>
#include "myalloc.h"

int test(int* ptr, int size);

int main(){
    int* ptr, ptr2;

    ptr = (int*)mymalloc(sizeof(int)*10);
    test(ptr, 10);

    ptr2 = (int*)mymalloc(sizeof(int)*10);
    test(ptr2, 10);

    myfree(ptr);

}

int test(int* ptr, int size){
    int i;
    if(ptr==0){
        printf("ERROR on mymalloc\n");
        return -1;
    }
    else{
        printf("%x is address.\n", ptr);
    }
    for(i=0;i<size;++i){
        ptr[i] = i;
    }
    for(i=0;i<size;++i){
        printf("%d\n", ptr[i]);
    }
}