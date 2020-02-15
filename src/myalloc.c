#include <stdlib.h>
#include <stdio.h>
#include "myalloc.h"

void * __mymalloc(int size){
    struct objstack* p;
    void* ret;
    p = hashlist[size];
    if(p == NULL){
        printf("yeah\n");
        // alloc new obj and init and return
        p = (struct objstack*)malloc(sizeof(struct objstack));
        for(int i = 0; i< ENTRY; i++){
            p->stack[i] = (struct obj*)malloc(sizeof(struct obj));
            p->stack[i]->real_space = malloc(size);
        }
        p->size = ENTRY;
        hashlist[size] = p;
    }

    if(p->size == 0){
        //This size is full. Try later.
        return 0;
    }
    else{
        struct obj* retobj = stack_pop(p);
        --p->size;
        ret = retobj->real_space;
        retobj->free = 0;
        return ret;
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
    s->size--;
    return s->stack[s->index++];
}

int stack_push(struct objstack* s, struct obj* target){
    if(s->size == ENTRY){
        return 0;
    }
    ++s->size;
    int newindex = s->index + 1;
    if(newindex > ENTRY){
        newindex -= ENTRY;
    }
    s->stack[newindex] = target;
    return 1;
}

void* hugealloc(int size){
    //#TODO
}

int myfree(void* target){
    //TODO
}

