#include <stdlib.h>
#include <stdio.h>
#include "darray.h"

Darray newDarray(int size){
    Darray da = (Darray)malloc(sizeof(struct darray));
    da->len = 0;
    da->size = size;
    da->array = (void**)malloc(sizeof(void*) * size);

    return da;
}

void* removeDarray(Darray da, int index){
    void* res;
    if(index>=da->len || index<0){
        fprintf(stderr,"Index %d of dynamic array out of bound\n", index);
        fprintf(stderr,"len %d \n", da->len);
        return NULL;
    }
    res = da->array[index];
    da->array[index] = NULL;
    return res;
}

void addDarray(Darray da, void* pt){
    if(da->len == da->size){
        da->size *= 2;
        da->array = (void**)realloc(da->array, sizeof(void*) * (da->size) );
    }
    da->array[da->len] = pt;
    da->len += 1;
}

void* getPos(Darray da, int index){
    if( index>=da->len || index<0 ) return NULL;
    return da->array[index]; 
}

