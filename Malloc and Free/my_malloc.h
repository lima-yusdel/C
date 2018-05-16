#ifndef _MY_MALLOC_H__
#define _MY_MALLOC_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x ,__FILE__ ,__LINE__)
#define memSize 5000
typedef struct _Node
{
        struct _Node *prev, *next;
        unsigned short  isFree;
        unsigned short size;
}Node;

struct timespec now, tmstart;

void *mymalloc(unsigned short size, char *file, int line);
void myfree(void *p, char *file, int line);

#endif
