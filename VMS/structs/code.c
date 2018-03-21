#include <stdlib.h>
#include "code.h"


extern Code code;


void codeInit(int size){
    code.array = newDarray(size);
    code.pc = 0;
}

CodeElem newCodeElem(Einst inst, Value f, Value s){
    CodeElem ce = (CodeElem)malloc(sizeof(struct codeElem));

    ce->inst = inst;
    ce->first = f;
    ce->second = s;

    return ce;
}

void addCode(CodeElem ce){
    addDarray(code.array, ce);
}

CodeElem getCode(){
    return getPos(code.array, code.pc);
}


