#ifndef HEAP_H
#define HEAP_H

#include "types.h"
#include "linkedList.h"
#include <glib.h>

typedef struct heapInfo{
    heapPt pt;
    int index;
} *HeapInfo;

typedef struct heap{
    LinkedList ll;
    GString* h;
    int last;
} Heap;

int Heap_remove(heapPt);
int Heap_getBlock(heapPt, GString*);
heapPt Heap_alloc(GString);

void Heap_init(int);
HeapInfo newHeapInfo(heapPt, int);

#endif
