#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

#include "types.h"


Value newValue(Uvalue val, Etype type){
    Value v;
    v.val = val;
    v.type = type;

    return v;
}

char* Value_toString(Value v){
    char* ret = (char*)malloc(MAX_LINE*sizeof(char));
/*    switch(v.type){
        case T_int      : snprintf(ret, 100, "[%d|%d]", T_int       , v.val.i);     break; 
        case T_float    : snprintf(ret, 100, "[%d|%f]", T_float     , v.val.f);     break; 
        case T_codePt   : snprintf(ret, 100, "[%d|%d]", T_codePt    , v.val.c);     break; 
        case T_heapPt   : snprintf(ret, 100, "[%d|%d]", T_heapPt    , v.val.h);     break; 
        case T_opPt     : snprintf(ret, 100, "[%d|%d]", T_opPt      , v.val.o);     break; 
        case NOTHING    : snprintf(ret, 100, "[%d|]"  , NOTHING);   break; 
    }*/
    switch(v.type){
        case T_int      : snprintf(ret, 100, "[%d|INT]",    v.val.i);   break; 
        case T_float    : snprintf(ret, 100, "[%f|FLOAT]",  v.val.f);   break; 
        case T_codePt   : snprintf(ret, 100, "[%d|CODE_PT]",v.val.c);   break; 
        case T_heapPt   : snprintf(ret, 100, "[%d|HEAP_PT]",v.val.h);   break; 
        case T_opPt     : snprintf(ret, 100, "[%d|OP_PT]",  v.val.o);   break; 
        case T_string   : snprintf(ret, 100, "[%s|STRING]", v.val.s->str); break;
        case NOTHING    : snprintf(ret, 100, "");   break; 
    }
    return ret;
}

char* Inst_toString(Einst i){
    char* ret = (char*)malloc(MAX_LINE*sizeof(char));
    switch(i){
        case ADD    : snprintf(ret, 100, "ADD   "); break; 
        case SUB    : snprintf(ret, 100, "SUB   "); break; 
        case MUL    : snprintf(ret, 100, "MUL   "); break; 
        case DIV    : snprintf(ret, 100, "DIV   "); break; 
        case MOD    : snprintf(ret, 100, "MOD   "); break; 
        case NOT    : snprintf(ret, 100, "NOT   "); break; 
        case INF    : snprintf(ret, 100, "INF   "); break; 
        case INFEQ  : snprintf(ret, 100, "INFEQ "); break; 
        case SUP    : snprintf(ret, 100, "SUP   "); break; 
        case SUPEQ  : snprintf(ret, 100, "SUPEQ "); break; 
        case FADD   : snprintf(ret, 100, "FADD  "); break; 
        case FSUB   : snprintf(ret, 100, "FSUB  "); break; 
        case FMUL   : snprintf(ret, 100, "FMUL  "); break; 
        case FDIV   : snprintf(ret, 100, "FDIV  "); break; 
        case FINF   : snprintf(ret, 100, "FINF  "); break; 
        case FINFEQ : snprintf(ret, 100, "FINFEQ"); break; 
        case FSUP   : snprintf(ret, 100, "FSUP  "); break; 
        case FSUPEQ : snprintf(ret, 100, "FSUPEQ"); break; 
        case PADD   : snprintf(ret, 100, "PADD  "); break; 
        case CONCAT : snprintf(ret, 100, "CONCAT"); break; 
        case ALLOC  : snprintf(ret, 100, "ALLOC "); break; 
        case ALLOCN : snprintf(ret, 100, "ALLOCN"); break; 
        case FREE   : snprintf(ret, 100, "FREE  "); break; 
        case EQUAL  : snprintf(ret, 100, "EQUAL "); break; 
        case ATOI   : snprintf(ret, 100, "ATOI  "); break; 
        case ATOF   : snprintf(ret, 100, "ATOF  "); break; 
        case ITOF   : snprintf(ret, 100, "ITOF  "); break; 
        case FTOI   : snprintf(ret, 100, "FTOI  "); break; 
        case STRI   : snprintf(ret, 100, "STRI  "); break; 
        case STRF   : snprintf(ret, 100, "STRF  "); break; 
        case PUSHI  : snprintf(ret, 100, "PUSHI "); break; 
        case PUSHN  : snprintf(ret, 100, "PUSHN "); break; 
        case PUSHF  : snprintf(ret, 100, "PUSHF "); break; 
        case PUSHS  : snprintf(ret, 100, "PUSHS "); break; 
        case PUSHG  : snprintf(ret, 100, "PUSHG "); break; 
        case PUSHL  : snprintf(ret, 100, "PUSHL "); break; 
        case PUSHSP : snprintf(ret, 100, "PUSHSP"); break; 
        case PUSHFP : snprintf(ret, 100, "PUSHFP"); break; 
        case PUSHGP : snprintf(ret, 100, "PUSHGP"); break; 
        case LOAD   : snprintf(ret, 100, "LOAD  "); break; 
        case LOADN  : snprintf(ret, 100, "LOADN "); break; 
        case DUP    : snprintf(ret, 100, "DUP   "); break; 
        case DUPN   : snprintf(ret, 100, "DUPN  "); break; 
        case POP    : snprintf(ret, 100, "POP   "); break; 
        case POPN   : snprintf(ret, 100, "POPN  "); break; 
        case STOREL : snprintf(ret, 100, "STOREL"); break; 
        case STOREG : snprintf(ret, 100, "STOREG"); break; 
        case STORE  : snprintf(ret, 100, "STORE "); break; 
        case STOREN : snprintf(ret, 100, "STOREN"); break; 
        case CHECK  : snprintf(ret, 100, "CHECK "); break; 
        case SWAP   : snprintf(ret, 100, "SWAP  "); break; 
        case WRITE  : snprintf(ret, 100, "WRITE "); break; 
        case READ   : snprintf(ret, 100, "READ  "); break; 
        case JUMP   : snprintf(ret, 100, "JUMP  "); break; 
        case JZ     : snprintf(ret, 100, "JZ    "); break; 
        case PUSHA  : snprintf(ret, 100, "PUSHA "); break; 
        case CALL   : snprintf(ret, 100, "CALL  "); break; 
        case RETURN : snprintf(ret, 100, "RETURN"); break; 
        case START  : snprintf(ret, 100, "START "); break; 
        case NOP    : snprintf(ret, 100, "NOP   "); break; 
        case ERR    : snprintf(ret, 100, "ERR   "); break; 
        case STOP   : snprintf(ret, 100, "STOP  "); break; 
    }
    return ret;
}

HashData newHashData(codePt line){
    HashData hd = (HashData)malloc(sizeof(struct hashData));
    hd->line = line;
    return hd;
}

