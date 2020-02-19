#include <stdlib.h>
#include <stdio.h>
#include "myalloc.h"


int __myfree(void* target, int size){
    struct objstack* p;

    p = hashlist[size];
    if(!stack_push(p, target))
        return 0;
    return 1;
}

int myfree(void* target){
    int size = *(int*)(target - 4);
    if(size > MAXSIZE)
        return hugefree(target - 4);
    else
        return __myfree(target - 4, size);
    
}

void * __mymalloc(int size){
    struct objstack* p;
    void* ret;
    p = hashlist[size];
    if(p == NULL){
        // alloc new obj and init and return
        p = (struct objstack*)malloc(sizeof(struct objstack));
        for(int i = 0; i< ENTRY; i++){
            p->stack[i] = malloc(size+4);
            *(int*)p->stack[i] = size;
        }
        p->index = 0;
        p->stacksize = ENTRY;
        hashlist[size] = p;
    }
    ret = stack_pop(p);
    //The stack is empty. Try later.
    if(ret == NULL)
        return NULL;
    else
        return ret+4;
}

void* mymalloc(int size){
    if(size > MAXSIZE){
        return hugealloc(size);
    }
    else{
        return __mymalloc(size);
    }
}

void* stack_top(struct objstack* s){
    return s->stack[s->index];
}

void* stack_pop(struct objstack* s){
    if(s->stacksize == 0)
        return NULL;
    --s->stacksize;
    return s->stack[s->index++];
}

int stack_push(struct objstack* s, void* target){
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

void* hugefree(void* target){
    //#TODO
}
