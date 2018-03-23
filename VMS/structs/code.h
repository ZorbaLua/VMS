#ifndef CODE_H
#define CODE_H

#include "types.h"
#include "darray.h"


typedef struct codeElem{
    Einst inst;
    Value first;
    Value second;
} *CodeElem;

typedef struct code{
    Darray array;
    int pc;
} Code;

void codeInit(int);
CodeElem newCodeElem(Einst, Uvalue, Etype, Uvalue, Etype);
void addCode(CodeElem);
CodeElem getCode();

#endif
