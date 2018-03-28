
#include <stdlib.h>
#include <stdio.h>
#include "array.h"

int Array_remove(Array* self, int index, void** ret) {
    if(index>=self->len || index<0) return -1;
    if(index+1 == self->len) self->len--;
    *ret = self->array[index];
    self->array[index] = NULL;
    return 0;
}

int Array_getPos(Array* self, int index, void** ret) {
    if(index>=self->len || index<0) return -1;
    *ret = self->array[index];
    return 0;
}

void Array_add(Array* self, void* pt) {
    if(self->len == self->size) {
        self->size *= 2;
        self->array = (void**)realloc(self->array, self->size*sizeof(void*) );
    }
    self->array[self->len] = pt;
    self->len += 1;
}

void Array_init(Array* self, int size) {
    (*self).len = 0;
    (*self).size = size;
    (*self).array = (void**)malloc(sizeof(void*) * size);
}
