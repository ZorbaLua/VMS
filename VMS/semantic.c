#include "semantic.h"

#include "structs/code.h"
#include "structs/opStack.h"

extern Code code;
extern OpStack opStack;

void semPushi(Value v){
    OperandElem oe = newOperandElem(v);
    push(oe);
    code.pc += 1;
}

