#include <stdio.h>
#include "myalloc.h"

int test(int* ptr, int size);

int main(){
    int *ptr[ENTRY];
    for(int i = 0; i<ENTRY; i++){
        ptr[i] = (int*)mymalloc(sizeof(int)*10);
        test(ptr[i], 10);
    }
    for(int i = 0; i<ENTRY; i++){
        myfree(ptr[i]);
    }

}

int test(int* ptr, int size){
    int i;
    if(ptr==0){
        printf("ERROR on mymalloc\n");
        return -1;
    }
    else{
        printf("%p is address.\n", ptr);
    }
    for(i=0;i<size;++i){
        ptr[i] = i;
    }
    for(i=0;i<size;++i){
        printf("%d\n", ptr[i]);
    }
}