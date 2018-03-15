#include "darray.h"

Darray newDarray(char type, int size){
    Darray da = (Darray)malloc(sizeof(struct darray));
    da->len = 0;
    da->size = size;
    da->type = type;
    da->node = (Node*)malloc(sizeof(union node)*size);

    return da;
}

void addDarray(Darray da, Node n){
    if(da->len == da->size){
        da->size *= 2;
        da->node = (Node*)realloc(da->node, sizeof(union node)*(da->size) );
    }
     da->node[da->len++] = n;
}

