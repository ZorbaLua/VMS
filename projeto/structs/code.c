#include <stdlib.h>
#include <stdio.h>
#include "code.h"

extern Code code;

char* Code_toString(CodeElem ce){
    char* ret = (char*)malloc(MAX_LINE*sizeof(char));
    snprintf(ret, MAX_LINE, "(%d:%s:%s)", ce->inst, Value_toString(ce->first), Value_toString(ce->second));
    return ret;
}

void Code_add(CodeElem ce){
    printCode(ce, '+');
    Array_add(&code.array, ce);
}

int Code_get(CodeElem* ret){
    return Array_getPos(&code.array, code.pc++, (void**)ret);
}

void Code_init(int size){
    Array_init(&code.array, size);
    code.pc = 0;
}

CodeElem newCodeElem(Einst inst, Value v1, Value v2){
    CodeElem ce = (CodeElem)malloc(sizeof(struct codeElem));

    ce->inst = inst;
    ce->first = v1;
    ce->second = v2;

    return ce;
}

void printCode(CodeElem ce, char signal){
    printf("CODE\t\t(%d)\t\t%c(%d:%s:%s)\n", code.pc, signal,ce->inst, Value_toString(ce->first), Value_toString(ce->second));
}
