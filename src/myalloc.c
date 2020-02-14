#include <stdlib.h>
#include <stdio.h>
#include "myalloc.h"

void * __mymalloc(int size){
    struct objlist* p;
    void* ret;
    p = hashlist[size];
    if(p == NULL){
        printf("yeah\n");
        // alloc new obj and init and return
        p = (struct objlist*)malloc(sizeof(struct objlist));
        for(int i = 0; i< ENTRY; i++){
            p->map[i] = malloc(sizeof(struct obj));
            p->map[i]->free = 1;
            p->map[i]->real_space = malloc(size);
        }
        p->size = size;
        p->freecount = ENTRY;
        p->freeobj = p->map[0];
        hashlist[size] = p;
    }

    if(p->freecount == 0){
        //This size is full. Try later.
        return 0;
    }
    else{
        struct obj* retobj = p->freeobj;
        --p->freecount;
        ret = retobj->real_space;
        retobj->free = 0;
        replace_freeobj(p);
        return ret;
    }
}

void replace_freeobj(struct objlist* p){
    struct obj *iter;
    int i;
    for(i=0; i<ENTRY; ++i){
        iter = p->map[i];
        if(iter->free == 1){
            p->freeobj = iter;
        }
    }
}

void* mymalloc(int size){
    if(size > MAXSIZE){
        return hugealloc(size);
    }
    else{
        return __mymalloc(size);
    }
}

void* hugealloc(int size){
    //#TODO
}

int myfree(void* target){
    //TODO
}