#ifndef DARRAY_H
#define DARRAY_H

#include "nodes.h"



typedef struct darray{
    int len;
    int size;
    char type;
    Node* node;
} *Darray;


Darray newDarray(char type, int size);
void addDarray(Darray da, Node n);


#endif
