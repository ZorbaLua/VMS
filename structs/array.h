#ifndef DARRAY_H
#define DARRAY_H

#include "nodes.h"



typedef struct codeStack{
    int len;
    int size;
    char type;
    NodeCode* nc;
} *CodeStack;


CodeStack newCodeSatc();
void addCodeStack(CodeStack cs, NodeCode n);


#endif
