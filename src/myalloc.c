#include <stdlib.h>
#include <stdio.h>
#include "myalloc.h"


int myfree(void* target){
    int size = *(int*)(&target + 4);
    printf("free size:%d\n", size);
}


void * __mymalloc(int size){
    struct objstack* p;
    struct obj* ret;
    p = hashlist[size];
    if(p == NULL){
        // alloc new obj and init and return
        p = (struct objstack*)malloc(sizeof(struct objstack));
        for(int i = 0; i< ENTRY; i++){
            p->stack[i] = (struct obj*)malloc(sizeof(struct obj));
            p->stack[i]->real_space = malloc(size);
        }
        p->index = 0;
        p->stacksize = ENTRY;
        hashlist[size] = p;
    }
    ret = stack_pop(p);
    if(ret == NULL){
        //This size is empty. Try later.
        return NULL;
    }
    else{
        return ret->real_space;
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

struct obj* stack_top(struct objstack* s){
    return s->stack[s->index];
}

struct obj* stack_pop(struct objstack* s){
    if(s->stacksize == 0)
        return NULL;
    --s->stacksize;
    return s->stack[s->index++];
}

int stack_push(struct objstack* s, struct obj* target){
    if(s->stacksize == ENTRY){
        return 0;
    }
    ++s->stacksize;
    int newindex = s->index - 1;
    if(newindex < 0){
        newindex += ENTRY;
    }
    s->stack[newindex] = target;
    --s->index;
    return 1;
}

void* hugealloc(int size){
    //#TODO
}
