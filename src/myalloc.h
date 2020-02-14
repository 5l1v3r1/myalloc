#define MAXSIZE 4096
#define ENTRY 1024

struct obj{
    int free;
    void* real_space;
};

struct objlist{
    int size;
    int freecount;
    struct obj* freeobj;
    struct obj* map[ENTRY];
};

static struct objlist* hashlist[MAXSIZE];

void * __mymalloc(int size);
void* hugealloc(int size);
void replace_freeobj(struct objlist* p);

extern void * mymalloc(int size);
extern int myfree(void* target);