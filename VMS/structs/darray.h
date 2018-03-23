#ifndef DARRAY_H
#define DARRAY_H


typedef struct darray{
    int len;
    int size;
    void** array;
} *Darray;


Darray newDarray(int);
void addDarray(Darray, void*);
void* removeDarray(Darray, int);
void* getPos(Darray, int);


#endif
