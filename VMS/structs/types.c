#include <stdlib.h>
#include "types.h"


Value newValue(Uvalue val, Etype type){
    Value v;
    v.val = val;
    v.type = type;

    return v;
}


