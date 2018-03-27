
#include <stdio.h>
#include "semantic.h"
#include "structs/code.h"
#include "structs/opStack.h"
#include "structs/callStack.h"

extern Code code;
extern OpStack opstack;
extern FILE* io;
extern FILE* extra;

int semPushi(Value v) {
    OperandElem oe = newOperandElem(v);
    OpStack_push(oe,'s');

    return 0;
}

int semPushf(Value v) {
    OperandElem oe = newOperandElem(v);
    OpStack_push(oe,'s');

    return 0;
}

int semWrite() {
    OperandElem oe = NULL;
    OpStack_pop(&oe);
    
    switch(oe->val.type){
        case T_int    : printf("OUTPUT:\t%d\n", oe->val.val.i); break;
        case T_float  : printf("OUTPUT:\t%f\n", oe->val.val.f); break;
        case T_codePt : printf("OUTPUT:\t%d\n", oe->val.val.c); break;
        case T_opPt   : printf("OUTPUT:\t%d\n", oe->val.val.o); break;
        case T_heapPt : printf("OUTPUT:\t%d\n", oe->val.val.h); break;
        case NOTHING: return -1;
    }
    return 0;
}

int semNot() {
    OperandElem oe = NULL;
    Uvalue uv;
    Value v;
    OpStack_pop(&oe);
    switch(oe->val.type){
        case T_int      : uv = (Uvalue)(oe->val.val.i == 0); break;
        case T_float    : uv = (Uvalue)(oe->val.val.f == 0); break;
        case T_codePt   : uv = (Uvalue)(oe->val.val.c == 0); break;
        case T_opPt     : uv = (Uvalue)(oe->val.val.o == 0); break;
        case T_heapPt   : uv = (Uvalue)(oe->val.val.h == 0); break;
        case NOTHING: return -1;
    }
    v = newValue(uv, T_int);
    OpStack_push(newOperandElem(v), 's');

    return 0;
}

int semAdd() {
    return 0;
}

int semSub() {
    return 0;
}

int semMul() {
    return 0;
}

int semDiv() {
    return 0;
}

int semMod() {
    return 0;
}


int semInf() {
 		return 0;
}

int semInfeq() {
 		return 0;
}

int semSup() {
 		return 0;
}

int semSupeq() {
 		return 0;
}

int semEq() {
 		return 0;
}

int semDif() {
 		return 0;
}

int semFadd() {
 		return 0;
}

int semFsub() {
 		return 0;
}

int semFmul() {
 		return 0;
}

int semFdiv() {
 		return 0;
}

int semFcos() {
        return 0;
}

int semFsin() {
 		return 0;
}

int semFtan() {
 		return 0;
}

int semFinf() {
 		return 0;
}

int semFinfeq() {
 		return 0;
}

int semFsup() {
 		return 0;
}

int semFsupeq() {
 		return 0;
}

int semFeq() {
 		return 0;
}

int semFdif() {
 		return 0;
}

int semPadd() {
 		return 0;
}

int semConcat() {
 		return 0;
}

int semAlloc() {
 		return 0;
}

int semAllocn() {
 		return 0;
}

int semFree() {
 		return 0;
}

int semEqual() {
 		return 0;
}

int semAtoi() {
 		return 0;
}

int semAtof() {
 		return 0;
}

int semItof() {
 		return 0;
}

int semFtoi() {
 		return 0;
}

int semStri() {
 		return 0;
}

int semStrf() {
 		return 0;
}

int semPushn() {
 		return 0;
}

int semPushs() {
 		return 0;
}

int semPushg() {
 		return 0;
}

int semPushl() {
 		return 0;
}

int semPushsp() {
 		return 0;
}

int semPushfp() {
 		return 0;
}

int semPushgp() {
 		return 0;
}

int semLoad() {
 		return 0;
}

int semLoadn() {
 		return 0;
}

int semDup() {
 		return 0;
}

int semDupn() {
 		return 0;
}

int semPop() {
 		return 0;
}

int semPopn() {
 		return 0;
}

int semStorel() {
 		return 0;
}

int semStoreg() {
 		return 0;
}

int semStore() {
 		return 0;
}

int semStoren() {
 		return 0;
}

int semCheck() {
 		return 0;
}

int semSwap() {
 		return 0;
}

int semRead() {
 		return 0;
}

int semReadi() {
 		return 0;
}

int semReadf() {
 		return 0;
}

int semReads() {
 		return 0;
}

int semJump() {
 		return 0;
}

int semJz() {
 		return 0;
}

int semPusha() {
 		return 0;
}

int semCall() {
 		return 0;
}

int semReturn() {
 		return 0;
}

int semStart() {
 		return 0;
}

int semNop() {
 		return 0;
}

int semErr() {
 		return 0;
}

int semStop() {
 		return 0;
}

int semLabel() {
 		return 0;
}
