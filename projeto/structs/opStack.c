#include <stdlib.h>
#include "opStack.h"

#include <stdio.h>


extern OpStack opstack;

int OpStack_pop(OperandElem* ret){
    int erro;
    if(opstack.sp == opstack.fp) return -1;
    opstack.sp -= 1;
    erro = Array_remove(&(opstack.stack), opstack.sp, (void**)ret);
    printOpStack(*ret, '-');
    return erro;
}

int OpStack_top(OperandElem* ret){
    return Array_getPos(&(opstack.stack), opstack.sp-1, (void**)ret);
}

void OpStack_push(OperandElem oe, char pt){
    Array_add(&(opstack.stack), oe);
    switch(pt){
        case 's': opstack.sp += 1; break;
        case 'g': opstack.gp += 1; break;
    }
    printOpStack(oe, '+');
}


void OpStack_init(int size){
    Array_init(&(opstack.stack), size);
    opstack.sp = 0;
    opstack.fp = 0;
    opstack.gp = 0;
}


OperandElem newOperandElem(Value v){
    OperandElem oe = (OperandElem)malloc(sizeof(struct operandElem));
    oe->val = v;
    return oe;
}

void printOpStack(OperandElem oe, char signal){
    printf("OPSTACK\t\t(%d,%d,%d)\t\t-%s\n", opstack.sp, opstack.fp, opstack.gp, Value_toString(oe->val));
}

