#include <stdlib.h>
#include "opStack.h"


extern OpStack opStack;

void push(OperandElem oe){
    addDarray(opStack.array, oe);
    opStack.sp += 1;
}


void opStackInit(int size){
    opStack.array = newDarray(size);
    opStack.sp = 0;
    opStack.fp = 0;
    opStack.gp = 0;
}


OperandElem newOperandElem(Value v){
    OperandElem oe = (OperandElem)malloc(sizeof(struct operandElem));

    oe->val = v;

    return oe;
}


