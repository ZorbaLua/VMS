#ifndef CODE_H
#define CODE_H

#include "types.h"
#include "array.h"


typedef struct codeElem{
    Einst inst;
    Value first;
    Value second;
} *CodeElem;

typedef struct code{
    Array array;
    int pc;
} Code;

void Code_add(CodeElem);
int  Code_get(CodeElem*);

void Code_init(int);
CodeElem newCodeElem(Einst, Uvalue, Etype, Uvalue, Etype);

#endif
