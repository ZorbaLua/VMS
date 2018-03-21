#include <stdlib.h>
#include "darray.h"

Darray newDarray(int size){
    Darray da = (Darray)malloc(sizeof(struct darray));
    da->len = 0;
    da->size = size;
    da->array = (void**)malloc(sizeof(void*) * size);

    return da;
}

void addDarray(Darray da, void* pt){
    if(da->len == da->size){
        da->size *= 2;
        da->array = (void**)realloc(da->array, sizeof(void*) * (da->size) );
    }
    da->array[da->len++] = pt;
}

void* getPos(Darray da, int index){
    if( index>=da->len || index<0 ) return NULL;
    return da->array[index]; 
}

