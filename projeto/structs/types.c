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
        case INT    : snprintf(ret, 100, "[%d|%d]", INT, v.val.i);     break; 
        case FLOAT  : snprintf(ret, 100, "[%d|%f]", FLOAT, v.val.f);   break; 
        case CODE_PT: snprintf(ret, 100, "[%d|%d]", CODE_PT, v.val.i); break; 
        case HEAP_PT: snprintf(ret, 100, "[%d|%d]", HEAP_PT, v.val.i); break; 
        case OP_PT  : snprintf(ret, 100, "[%d|%d]", OP_PT, v.val.i);   break; 
        case NOTHING: snprintf(ret, 100, "[%d|]"  , NOTHING);          break; 
    }
    return ret;
}

