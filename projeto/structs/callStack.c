
#include <stdlib.h>
#include "callStack.h"

#include <stdio.h>


extern CallStack callstack;
extern FILE* dbout;

int CallStack_pop(CallElem* ret) {
    int erro;
    erro = Array_remove(&(callstack.stack), callstack.stack.len, (void**)ret);
    printCallStack(*ret, '-');
    return erro;
}

void CallStack_push(CallElem oe){
    Array_add(&(callstack.stack), oe);
    printCallStack(oe, '+');
}

void CallStack_init(int size) {
    Array_init(&(callstack.stack), size);
}

CallElem newCallElem(codePt pc, opPt fp){
    CallElem ce = (CallElem)malloc(sizeof(struct callElem));
    ce->pc = pc;
    ce->fp = fp;
    return ce;
}

void printCallStack(CallElem ce, char signal) {
    fprintf(dbout, "> CALLSTACK %c %d %d %d\n", signal, callstack.stack.len , ce->pc, ce->fp);
    fflush(dbout);
}
