#include <stdlib.h>
#include "code.h"


extern Code code;


void codeInit(int size){
    code.array = newDarray(size);
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

void addCode(CodeElem ce){
    addDarray(code.array, ce);
}

CodeElem getCode(){
    code.pc += 1;
    return getPos(code.array, code.pc);
}


