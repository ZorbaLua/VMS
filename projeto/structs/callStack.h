
#ifndef CALLSTACK_H
#define CALLSTACK_H

#include "types.h"
#include "array.h"

typedef struct callElem{
    int pc;
    int fp;
} *CallElem;

typedef struct callStack{
    Array stack;
} CallStack;

int CallStack_pop(CallElem*);
void CallStack_push(CallElem);

CallElem newCallElem(codePt, opPt);
void CallStack_init(int);
void printCallStack(CallElem, char signal);
char* Call_toString(CallElem);

#endif
