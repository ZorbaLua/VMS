#include <stdlib.h>
#include "opStack.h"

#include <stdio.h>


extern OpStack opstack;

int OpStack_pop(OperandElem* ret){
    if(opstack.sp == opstack.fp) return -1;
    opstack.sp -= 1;
    return Array_remove(&opstack.array, opstack.sp, (void**)ret);
}

int OpStack_top(OperandElem* ret){
    return Array_getPos(&opstack.array, opstack.sp-1, (void**)ret);
}

void OpStack_push(OperandElem oe, char pt){
    Array_add(&opstack.array, oe);
    switch(pt){
        case 's': opstack.sp += 1;
        case 'g': opstack.gp += 1;
    }
}


void OpStack_init(int size){
    Array_init(&opstack.array, size);
    opstack.sp = 0;
    opstack.fp = 0;
    opstack.gp = 0;
}


OperandElem newOperandElem(Value v){
    OperandElem oe = (OperandElem)malloc(sizeof(struct operandElem));
    oe->val = v;
    return oe;
}


