#include <stdlib.h>
#include "callStack.h"

#include <stdio.h>


extern CallStack callstack;

int CallStack_pop(CallElem* ret){
    int erro;
    erro = Array_remove(&(callstack.stack), callstack.stack.len, (void**)ret);
    printCallStack(*ret, '-');
    return erro;
}


void CallStack_push(CallElem oe){
    Array_add(&(callstack.stack), oe);
    printCallStack(oe, '+');
}


void CallStack_init(int size){
    Array_init(&(callstack.stack), size);
}


CallElem newCallElem(codePt pc, opPt fp){
    CallElem ce = (CallElem)malloc(sizeof(struct callElem));
    ce->pc = pc;
    ce->fp = fp;

    return ce;
}

char* Call_toString(CallElem ce){
    char* ret = (char*)malloc(MAX_LINE*sizeof(char));
    snprintf(ret, MAX_LINE, "(%d:%d)", ce->pc, ce->fp);
    return ret;
}

void printCallStack(CallElem ce, char signal){
    printf("CallStack\t\t()\t\t-%s\n", Call_toString(ce));
}

