#ifndef OPSTACK_H
#define OPSTACK_H

#include "types.h"
#include "array.h"

typedef struct operandElem{
    Value val;
} *OperandElem;

typedef struct opStack{
    Array stack;
    int sp;
    int fp;
    int gp;
} OpStack;



int OpStack_pop(OperandElem*);
int OpStack_top(OperandElem*);
void OpStack_push(OperandElem, char pt);

OperandElem newOperandElem(Value);
void OpStack_init(int);
void printOpStack(OperandElem, char);

#endif
