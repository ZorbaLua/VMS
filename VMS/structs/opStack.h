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



int opsPop(OperandElem*);
int opsTop(OperandElem*);
void opsPush(OperandElem, char pt);
OperandElem newOperandElem(Value);
void opStackInit(int);

#endif
