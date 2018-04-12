
#ifndef HEAP_H
#define HEAP_H

#include "types.h"
#include <glib.h>

typedef struct heapInfo{
    heapPt pt;
    int len;
} *HeapInfo;

typedef struct heap{
    GString* h;
    int last;
} Heap;

int Heap_free(heapPt);
void Heap_getBlock(heapPt, char*);
heapPt Heap_alloc(char*, int);

void Heap_init(int);
HeapInfo newHeapInfo(heapPt, int);

#endif
