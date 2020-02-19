#define MAXSIZE 4096
#define ENTRY 1024

struct objstack{
    int stacksize;
    int index;
    void* stack[ENTRY];
};

void * __mymalloc(int size);
void* hugealloc(int size);
int hugefree(void* target);
void* stack_top(struct objstack* s);
void* stack_pop(struct objstack* s);
int stack_push(struct objstack* s, void* target);

extern void * mymalloc(int size);
extern int myfree(void* target);