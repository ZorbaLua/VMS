#include <stdio.h>

#include "heap.h"

extern Heap heap;

HeapElem* get(heapPt pt){
    if((heap.mem)[pt].c == '\0' || pt<0 || pt>heap.size) return NULL;
    return &(heap.mem[pt]);
}

char* Heap_getBlock(heapPt pt){
    HeapElem *he=NULL, *prox=NULL;
    int i, len = 100;
    char* ret = (char*)malloc(len*sizeof(char));
    if( !(he = get(pt)) ) return "\0";
    i=0;
    while(prox){
        if(i<len-1) ret = (char*)realloc(&ret, len*sizeof(char));
        he = prox;
        ret[i] = he->c; 
        prox = get(he->next);
        i++;
    }
    ret[i] = '\0';
    return ret;
}

void Heap_free(heapPt pt){
    HeapElem *he=NULL, *prox=NULL;
    if( (he = get(pt)) == NULL ) return;
    while(prox){
        he = prox;
        he->c = '\0'; 
        prox = get(he->next);
    }
    (heap.mem)[he->next].next = heap.first;
    heap.first = pt;
}

void alloc(char c){
    int size = heap.size;
    HeapElem* he;
    if(heap.first == size){
        heap.size *= 2;
        heap.mem = (HeapElem*)realloc( &(heap.mem), (heap.size)*sizeof(HeapElem) );
        while(size < heap.size){
            he = get(size);
            he->c = '\0';
            he->next = size+1;
            size++;
        }
    }
    he = get(heap.first);
    he->c = c;
    heap.first = he->next;
}

heapPt Heap_alloc(char* s, int len){
    heapPt ret = heap.first;
    int i=0;
    while(i<len) alloc(s[i]);
    alloc('\0');
    return ret;
}


void Heap_init(int size){
    int i=0;
    HeapElem* he;
    heap.mem = (HeapElem*)malloc(size*sizeof(HeapElem));
    heap.size = size;
    heap.first = 0;
    while(i < heap.size){
        he = &((heap.mem)[i]);
        he->c = '\0';
        he->next = i+1;
        i++;
    }
}

