#include <stdlib.h>
#include <stdio.h>
#include "types.h"


Value newValue(Uvalue val, Etype type){
    Value v;
    v.val = val;
    v.type = type;

    return v;
}

char* Value_toString(Value v){
    char* ret = (char*)malloc(MAX_LINE*sizeof(char));
    switch(v.type){
        case T_int      : snprintf(ret, 100, "[%d|%d]", T_int       , v.val.i);     break; 
        case T_float    : snprintf(ret, 100, "[%d|%f]", T_float     , v.val.f);     break; 
        case T_codePt   : snprintf(ret, 100, "[%d|%d]", T_codePt    , v.val.c);     break; 
        case T_heapPt   : snprintf(ret, 100, "[%d|%d]", T_heapPt    , v.val.h);     break; 
        case T_opPt     : snprintf(ret, 100, "[%d|%d]", T_opPt      , v.val.o);     break; 
        case NOTHING    : snprintf(ret, 100, "[%d|]"  , NOTHING);   break; 
    }
    return ret;
}

