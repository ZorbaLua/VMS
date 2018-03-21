#ifndef DARRAY_H
#define DARRAY_H


typedef struct darray{
    int len;
    int size;
    void** array;
} *Darray;


Darray newDarray(int size);
void addDarray(Darray da, void* pt);
void* getPos(Darray da, int index);


#endif
