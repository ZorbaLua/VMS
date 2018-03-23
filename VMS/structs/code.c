#include <stdlib.h>
#include "code.h"

extern Code code;

void Code_add(CodeElem ce){
    Array_add(&code.array, ce);
}

int Code_get(CodeElem* ret){
    return Array_getPos(&code.array, code.pc++, (void**)ret);
}

void Code_init(int size){
    Array_init(&code.array, size);
    code.pc = 0;
}

CodeElem newCodeElem(Einst inst, Uvalue v1, Etype t1, Uvalue v2, Etype t2){
    CodeElem ce = (CodeElem)malloc(sizeof(struct codeElem));
    Value f = newValue(v1,t1);
    Value s = newValue(v2,t2);

    ce->inst = inst;
    ce->first = f;
    ce->second = s;

    return ce;
}
