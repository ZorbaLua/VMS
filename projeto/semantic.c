
#include <stdio.h>
#include <glib.h>

#include "semantic.h"
#include "structs/code.h"
#include "structs/opStack.h"
#include "structs/callStack.h"
#include "structs/heap.h"

extern Code code;
extern OpStack opstack;
extern FILE* io;
extern FILE* extra;

void try(int);

int semPushi(Value v) {
    OperandElem oe = newOperandElem(v);
    OpStack_push(oe);

    return 0;
}

int semPushf(Value v) {
    OperandElem oe = newOperandElem(v);
    OpStack_push(oe);

    return 0;
}

int semWrite() {
    OperandElem oe = NULL;
    try(OpStack_pop(&oe));
    
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
    try(OpStack_pop(&oe));
    switch(oe->val.type){
        case T_int      : uv.i = oe->val.val.i == 0; break;
        case T_float    : uv.i = oe->val.val.f == 0; break;
        case T_codePt   : uv.i = oe->val.val.c == 0; break;
        case T_opPt     : uv.i = oe->val.val.o == 0; break;
        case T_heapPt   : uv.i = oe->val.val.h == 0; break;
        case NOTHING: return -1;
    }
    v = newValue(uv, T_int);
    OpStack_push(newOperandElem(v));

    return 0;
}

int semEqual() {
    OperandElem top, other;
    Uvalue uv;
    Value v;
    try(OpStack_pop(&top));
    try(OpStack_pop(&other));
    if(top->val.type != other->val.type){
        uv.i = 0;
        v = newValue(uv, T_int);
        OpStack_push(newOperandElem(v));
    }
    else{
        switch(top->val.type){
            case T_int      : uv.i = top->val.val.i == other->val.val.i; break;
            case T_float    : uv.i = top->val.val.f == other->val.val.f; break;
            case T_codePt   : uv.i = top->val.val.c == other->val.val.c; break;
            case T_opPt     : uv.i = top->val.val.o == other->val.val.o; break;
            case T_heapPt   : uv.i = top->val.val.h == other->val.val.h; break;
            case NOTHING    : return -1;
        }
        v = newValue(uv, T_int);
        OpStack_push(newOperandElem(v));
    }
 	return 0;
}

void operationsInt(char op){
    OperandElem top, other;
    Uvalue uv;
    Value v;
    try(OpStack_pop(&top));
    try(OpStack_pop(&other));
    switch(op){
        case '+': uv.i = other->val.val.i +  top->val.val.i;    break; 
        case '-': uv.i = other->val.val.i -  top->val.val.i;    break;
        case '*': uv.i = other->val.val.i *  top->val.val.i;    break;
        case '/': uv.i = other->val.val.i /  top->val.val.i;    break;
        case '%': uv.i = other->val.val.i %  top->val.val.i;    break;
        case 's': uv.i = other->val.val.i >  top->val.val.i;    break;
        case 'S': uv.i = other->val.val.i >= top->val.val.i;    break;
        case 'i': uv.i = other->val.val.i <  top->val.val.i;    break;
        case 'I': uv.i = other->val.val.i <= top->val.val.i;    break;
    }
    v = newValue(uv, T_int);
    OpStack_push(newOperandElem(v));
}

void operationsFloat(char op){
    OperandElem top, other;
    Uvalue uv;
    Value v;
    try(OpStack_pop(&top));
    try(OpStack_pop(&other));
    switch(op){
        case '+': uv.f = other->val.val.f +  top->val.val.f;    break; 
        case '-': uv.f = other->val.val.f -  top->val.val.f;    break;
        case '*': uv.f = other->val.val.f *  top->val.val.f;    break;
        case '/': uv.f = other->val.val.f /  top->val.val.f;    break;
        case 's': uv.f = other->val.val.f >  top->val.val.f;    break;
        case 'S': uv.f = other->val.val.f >= top->val.val.f;    break;
        case 'i': uv.f = other->val.val.f <  top->val.val.f;    break;
        case 'I': uv.f = other->val.val.f <= top->val.val.f;    break;
    }
    v = newValue(uv, T_float);
    OpStack_push(newOperandElem(v));
}

int semAdd() {
    operationsInt('+'); 
    return 0;
}

int semSub() {
    operationsInt('-'); 
    return 0;
}

int semMul() {
    operationsInt('*'); 
    return 0;
}

int semDiv() {
    operationsInt('/'); 
    return 0;
}

int semMod() {
    operationsInt('%'); 
    return 0;
}

int semInf() {
    operationsInt('i'); 
 	return 0;
}

int semInfeq() {
    operationsInt('I'); 
 	return 0;
}

int semSup() {
    operationsInt('s'); 
 	return 0;
}

int semSupeq() {
    operationsInt('S'); 
 	return 0;
}

int semFadd() {
    operationsFloat('+');
 	return 0;
}

int semFsub() {
    operationsFloat('-');
 	return 0;
}

int semFmul() {
    operationsFloat('*');
 	return 0;
}

int semFdiv() {
    operationsFloat('/');
 	return 0;
}

int semFinf() {
    operationsFloat('i');
 	return 0;
}

int semFinfeq() {
    operationsFloat('I');
 	return 0;
}

int semFsup() {
    operationsFloat('s');
 	return 0;
}

int semFsupeq() {
    operationsFloat('S');
 	return 0;
}

int semPadd() {
    OperandElem pt, integer;
    Uvalue uv;
    try(OpStack_pop(&pt));
    try(OpStack_pop(&integer));
    if( integer->val.type != T_int ) return -1;
    switch(pt->val.type){
        case T_codePt: 
            uv.c = pt->val.val.c + integer->val.val.i; 
            OpStack_push(newOperandElem(newValue(uv, T_codePt)));
            break;
        case T_opPt:
            uv.o = pt->val.val.o + integer->val.val.i;
            OpStack_push(newOperandElem(newValue(uv, T_opPt)));
            break;
        case T_heapPt:
            uv.h = pt->val.val.h + integer->val.val.i; 
            OpStack_push(newOperandElem(newValue(uv, T_heapPt)));
            break;
        default: return -1;
    }
 	return 0;
}

int semConcat() {
 	return 0;
}

int semAlloc(Value f) {
    Uvalue uv;
    GString* s = g_string_sized_new(f.val.i);
    uv.h = Heap_alloc(*s);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));

 	return 0;
}

int semAllocn() {
    Uvalue uv;
    OperandElem oe;
    GString* s;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_int) return -1;
    s = g_string_sized_new(oe->val.val.i);
    uv.h = Heap_alloc(*s);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));

 	return 0;
}

int semFree() {
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

int semPushn(Value f) {
    int i, n = f.val.i;
    for(i=0; i<n; i++) OpStack_push(newOperandElem(newValue((Uvalue)0, T_int)));

 	return 0;
}

int semPushs() {
 	return 0;
}

int semPushg(Value f) {
    int index = f.val.i;
    OperandElem oe;
    try(OpStack_getPos(opstack.gp+index, &oe));
    OpStack_push(newOperandElem(newValue(oe->val.val, oe->val.type)));
 	return 0;
}

int semPushl(Value f) {
    int index = f.val.i;
    OperandElem oe;
    try(OpStack_getPos(opstack.fp+index, &oe));
    OpStack_push(newOperandElem(newValue(oe->val.val, oe->val.type)));
 	return 0;
}

int semPushsp() {
    OpStack_push(newOperandElem(newValue((Uvalue)opstack.sp, T_opPt)));
 	return 0;
}

int semPushfp() {
    OpStack_push(newOperandElem(newValue((Uvalue)opstack.fp, T_opPt)));
 	return 0;
}

int semPushgp() {
    OpStack_push(newOperandElem(newValue((Uvalue)0, T_opPt)));
 	return 0;
}

int semLoad() {
 	return 0;
}

int semLoadn() {
 	return 0;
}

int semDup(Value f) {
    int i, topo; 
    i = f.val.i;
    OperandElem oe;
    if(opstack.flagGlobal) topo = opstack.gp;
    else topo = opstack.sp;
    topo -= 1;
    while( i++ >= 0 ){
        try(OpStack_getPos(topo-i, &oe));
        OpStack_push(newOperandElem(newValue(oe->val.val, oe->val.type)));
    }

 	return 0;
}

int semDupn() {
    int i, topo; 
    OperandElem oe;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_int) return -1;
    i = oe->val.val.i;
    if(opstack.flagGlobal) topo = opstack.gp;
    else topo = opstack.sp;
    topo -= 1;
    while( i++ >= 0 ){
        try(OpStack_getPos(topo-i, &oe));
        OpStack_push(newOperandElem(newValue(oe->val.val, oe->val.type)));
    }
 	return 0;
}

int semPop(Value f) {
    int i, n = f.val.i;
    OperandElem oe;
    for(i=0; i<n; i++) try(OpStack_pop(&oe));
 	return 0;
}

int semPopn() {
    int i, n;
    OperandElem oe;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_int) return -1;
    n = oe->val.val.i;
    for(i=0; i<n; i++) try(OpStack_pop(&oe));
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
    opstack.flagGlobal = 0;
    opstack.fp = opstack.gp; 
    opstack.sp = opstack.gp;
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
