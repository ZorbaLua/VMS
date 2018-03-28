#include <stdlib.h>
#include "callStack.h"

#include <stdio.h>


extern CallStack callstack;

int CallStack_pop(CallElem* ret) {
    int erro;
    erro = Array_remove(&(callstack.stack), callstack.stack.len, (void**)ret);
    printCallStack(*ret, '-');
    return erro;
}

void CallStack_push(CallElem oe, char pt) {
    Array_add(&(callstack.stack), oe);
    printCallStack(oe, '+');
}

void CallStack_init(int size) {
    Array_init(&(callstack.stack), size);
}

CallElem newCallElem(int pc,  int fp) {
    CallElem ce = (CallElem)malloc(sizeof(struct callElem));
    ce->cpc = pc;
    ce->cfp = fp;

    return ce;
}

char* Call_toString(CallElem ce) {
    char* ret = (char*)malloc(MAX_LINE*sizeof(char));
    snprintf(ret, MAX_LINE, "(%d:%d)", ce->cpc, ce->cfp);
    return ret;
}

void printCallStack(CallElem ce, char signal) {
    printf("CallStack\t\t()\t\t-%s\n", Call_toString(ce));
}
