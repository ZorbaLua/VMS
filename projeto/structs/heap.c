#include <stdio.h>

#include "linkedList.h"
#include "heap.h"

extern Heap heap;

extern void try(int);


int Heap_free(heapPt pt){
    LinkedList ite;
    HeapInfo hi;
    for(ite = heap.ll; !ite; LinkedList_next(ite)){
        if( ((HeapInfo)ite->data)->pt == pt ){ 
            LinkedList_remove(ite, (void**)&hi);
            return 0;
        }
    }
    return -1;
}

void Heap_getBlock(heapPt pt, char* ret){
    int i;
    for(i=0; heap.h->str[pt] != '\0' && i<MAX_LINE; i++) ret[i] = heap.h->str[pt];
    ret[i] = '\0';
}

heapPt Heap_alloc(char *s, int len){
    int ret = heap.last;
    if(len + heap.last > heap.h->len){
        GString* aux = g_string_sized_new((heap.h)->len*2);
        heap.h = g_string_assign(aux, heap.h->str);
    }
    strncpy(&(heap.h->str[heap.last]), s, len);
    heap.last += len;
    return ret;
}

void Heap_init(int size){
    heap.ll = NULL;
    heap.h = g_string_sized_new(size);
    heap.last = 0;
}

HeapInfo newHeapInfo(heapPt pt, int len){
    HeapInfo hi = (HeapInfo)malloc(sizeof(struct heapInfo));
    hi->pt = pt;
    hi->len = len+1;

    return hi;
}
