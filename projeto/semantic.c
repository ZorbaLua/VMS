
#include <stdio.h>
#include <glib.h>

#include "semantic.h"
#include "structs/code.h"
#include "structs/opStack.h"
#include "structs/callStack.h"
#include "structs/heap.h"

extern GHashTable* labels;
extern Code code;
extern OpStack opstack;
extern Heap heap;

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
        case T_int    : printf("OUTPUT:%d\n", oe->val.val.i); break;
        case T_float  : printf("OUTPUT:%f\n", oe->val.val.f); break;
        case T_codePt : printf("OUTPUT:%d\n", oe->val.val.c); break;
        case T_opPt   : printf("OUTPUT:%d\n", oe->val.val.o); break;
        case T_heapPt : printf("OUTPUT:%d\n", oe->val.val.h); break;
        default: return -1;
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
        default: return -1;
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
            default: return -1;
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
    Uvalue uv;
    char *first, *second, *res;
    int len;
    OperandElem top, other;
    try(OpStack_pop(&top));
    try(OpStack_pop(&other));
    if(top->val.type != other->val.type || top->val.type != T_heapPt) return -1;
    first = Heap_getBlock(top->val.val.h);
    second = Heap_getBlock(other->val.val.h);
    len = strlen(first);
    len += strlen(second);
    res = (char*)malloc(len*sizeof(char));
    snprintf(res, len, "%s%s", first, second);
    uv.h = Heap_alloc(res, len);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));
    free(first); free(second); free(res);
 	return 0;
}

int semAlloc(Value f) {
    Uvalue uv;
    int i, len;
    len = f.val.i;
    char* s = (char*)malloc(sizeof(char) * len);
    for(i=0; i < len; i++) s[i] = '0';
    uv.h = Heap_alloc(s, len);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));
 	return 0;
}

int semAllocn() {
    Uvalue uv;
    OperandElem oe;
    int i, len;
    char* s;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_int) return -1;
    len = oe->val.val.i;
    s = (char*)malloc(sizeof(char) * len);
    for(i=0; i < oe->val.val.i; i++) s[i] = '0';
    uv.h = Heap_alloc(s,len);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));
 	return 0;
}

int semFree() {
    OperandElem oe;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_heapPt) return -1;
    Heap_free(oe->val.val.h);
 	return 0;
}

int semAtoi() {
    char* s;
    Uvalue uv;
    OperandElem oe;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_heapPt) return -1;
    s = Heap_getBlock(oe->val.val.h);
    uv.i = atoi(s);
    OpStack_push(newOperandElem(newValue(uv, T_int)));
    free(s);
 	return 0;
}

int semAtof() {
    char* s;
    Uvalue uv;
    OperandElem oe;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_heapPt) return -1;
    s = Heap_getBlock(oe->val.val.h);
    uv.i = atof(s);
    OpStack_push(newOperandElem(newValue(uv, T_float)));
    free(s);
 	return 0;
}

int semItof() {
    Uvalue uv;
    OperandElem oe;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_int) return -1;
    uv.f = (float)1.0 * (oe->val.val.i);
    OpStack_push(newOperandElem(newValue(uv, T_float)));
 	return 0;
}

int semFtoi() {
    Uvalue uv;
    OperandElem oe;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_float) return -1;
    uv.i = (int)(oe->val.val.f);
    OpStack_push(newOperandElem(newValue(uv, T_float)));
 	return 0;
}

int semStri() {
    Uvalue uv;
    OperandElem oe;
    char *s = (char*)malloc(sizeof(char) * 15);
    int len;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_int) return -1;
    snprintf(s, 15, "%d", oe->val.val.i);
    len = strnlen(s, 15);
    uv.h = Heap_alloc(s, len);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));
    free(s);
 	return 0;
}

int semStrf() {
    Uvalue uv;
    OperandElem oe;
    char *s = (char*)malloc(sizeof(char) * 15);
    int len;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_float) return -1;
    snprintf(s, 15, "%f", oe->val.val.f);
    len = strnlen(s, 15);
    uv.h = Heap_alloc(s, len);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));
    free(s);
 	return 0;
}

int semPushn(Value f) {
    int i, n = f.val.i;
    for(i=0; i<n; i++) OpStack_push(newOperandElem(newValue((Uvalue)0, T_int)));
 	return 0;
}

int semPushs(Value f) {
    Uvalue uv;
    uv.h = Heap_alloc(f.val.s->str, f.val.s->len);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));
 	return 0;
}

int semPushg(Value f) {
    int index = f.val.i;
    OperandElem oe;
    try(OpStack_getPos(0+index, &oe));
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

int semStorel(Value f) {
    OperandElem oe;
    try(OpStack_pop(&oe));
    try( OpStack_addPos(opstack.fp + f.val.i, newOperandElem(newValue(oe->val.val, oe->val.type))) );
 	return 0;
}

int semStoreg(Value f) {
    OperandElem oe;
    try(OpStack_pop(&oe));
    try( OpStack_addPos(opstack.gp + f.val.i, newOperandElem(newValue(oe->val.val, oe->val.type))) );
 	return 0;
}

int semStore(Value f) {
    /*OperandElem v, pt;
    try(OpStack_pop(&v));
    try(OpStack_pop(&pt));
    if(oe->val.type == )
 	*/
    return 0;
}

int semStoren() {
 	return 0;
}

int semCheck() {
 	return 0;
}

int semSwap() {
    OperandElem top, other;
    try(OpStack_pop(&top));
    try(OpStack_pop(&other));
    OpStack_push(top);
    OpStack_push(other);
 	return 0;
}

int semRead() {
    int len;
    Uvalue uv;
    heapPt pt;
    char* s = (char*)malloc(sizeof(char) * MAX_LINE);
    if(!fgets(s, MAX_LINE, stdin)) return -1;
    len = strnlen(s, MAX_LINE);
    pt = Heap_alloc(s, len);
    uv.h = Heap_alloc(s,len);
    OpStack_push(newOperandElem(newValue(uv, T_heapPt)));
 	return 0;
}

int semJump(Value f) {
    HashData hd = g_hash_table_lookup(labels, f.val.s->str);
    code.pc = hd->line;
 	return 0;
}

int semJz(Value f) {
    OperandElem oe;
    HashData hd;
    try(OpStack_pop(&oe));
    if(oe->val.type != T_int) return -1;
    if(oe->val.val.i == 0){
        hd = g_hash_table_lookup(labels, f.val.s->str);
        code.pc = hd->line;
    }
 	return 0;
}

int semPusha(Value f) {
    HashData hd = g_hash_table_lookup(labels, f.val.s->str);
    OpStack_push( newOperandElem(newValue((Uvalue)hd->line, T_codePt)) );
 	return 0;
}

int semCall() {
    OperandElem oe;
    CallStack_push(newCallElem(code.pc, opstack.fp));
    try(OpStack_pop(&oe));
    if(oe->val.type != T_codePt) return -1;
    code.pc = oe->val.val.c;
    opstack.fp = opstack.sp;
 	return 0;
}

int semReturn() {
    CallElem ce;
    try(CallStack_pop(&ce));
    opstack.sp = opstack.fp;
    code.pc = ce->pc;
    opstack.fp = ce->fp;
 	return 0;
}

int semStart() {
    opstack.flagGlobal = 0;
    opstack.fp = opstack.gp; 
    opstack.sp = opstack.gp;
 	return 0;
}

int semNop() {
    code.pc -= 1;
 	return 0;
}

int semErr() {
 	return 0;
}


