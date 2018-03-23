#include <stdlib.h>
#include "opStack.h"

#include <stdio.h>


extern OpStack opStack;

int opsPop(OperandElem* ret){
    if(opStack.sp == opStack.fp) return -1;
    *ret = removeDarray(opStack.array, opStack.sp-1);
    opStack.sp -=1;
    return 0;
}

int opsTop(OperandElem* ret){
    *ret = getPos(opStack.array, opStack.sp-1);
    return 0;
}

void opsPush(OperandElem oe, char pt){
    addDarray(opStack.array, oe);
    switch(pt){
        case 's': opStack.sp += 1;
        case 'g': opStack.gp += 1;
    }
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


