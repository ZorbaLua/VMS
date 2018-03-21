#ifndef OPSTACK_H
#define OPSTACK_H

#include "types.h"
#include "darray.h"

typedef struct operandElem{
    Value val;
} *OperandElem;

typedef struct opStack{
    Darray array;
    int sp;
    int fp;
    int gp;
} OpStack;



void push(OperandElem);
OperandElem newOperandElem(Value);
void opStackInit(int);

#endif
