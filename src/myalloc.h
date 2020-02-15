#define MAXSIZE 4096
#define ENTRY 1024

/*
struct obj{
    int free;
    void* real_space;
};

struct objstack{
    int size;
    int index;
    struct obj* stack[ENTRY];
};
*/

struct objstack{
    int size;
    int index;
    void* stack[ENTRY];
};

static struct objlist* hashlist[MAXSIZE];

void * __mymalloc(int size);
void* hugealloc(int size);
struct obj* stack_top(struct objstack* s);
struct obj* stack_pop(struct objstack* s);
int stack_push(struct objstack* s, struct obj* target);

extern void * mymalloc(int size);
extern int myfree(void* target);