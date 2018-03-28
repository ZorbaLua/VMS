#include "heap.h"

extern Heap heap;



int Heap_getBlock(heapPt pt, GString* ret){
    return 0;    
}

heapPt Heap_alloc(GString s){
    int ret = heap.last;
    if(s.len + heap.last > heap.h->len){
        GString* aux = g_string_sized_new((heap.h)->len*2);
        heap.h = g_string_assign(aux, heap.h->str);
    }

    strncpy(&(heap.h->str[heap.last]), s.str, s.len);
    heap.last += s.len;
    return ret;
}

void Heap_init(int size){
    heap.ll = NULL;
    heap.h = g_string_sized_new(size);
    heap.last = 0;
} 

HeapInfo newHeapInfo(heapPt pt, int index){
    HeapInfo hi = (HeapInfo)malloc(sizeof(struct heapInfo));
    hi->pt = pt;
    hi->index = index;

    return hi;
}
