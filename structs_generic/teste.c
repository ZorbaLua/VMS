#include <stdio.h>

#include "darray.h"
#include "nodes.h"

//#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#define Code(i) ((NodeCode)getPos(code,i)) 
#define addCode(...) addDarray(code, NewNodeCode(__VA_ARGS__))

#define Op(i) ((NodeOp)getPos(opstack,i)) 
#define addOp(...) addDarray(opstack, NewNodeOp(__VA_ARGS__))

int main(){
    Darray code = newDarray(1024);
    Darray opstack = newDarray(1024);
    //Darray callstack = newDarray(1024);

    //addDarray(da, NewNodeCode(0,2,1));
    addCode(0,1,1);
    addCode(0,"ola",1);
    addCode(0,2,"tudo");
    printf("code[1]|argumento 1: %s\n", Code(1)->a1.s);

    addOp('i',1);
    addOp('f',1.0f);
    addOp('f',2.0f);
    printf("opstack[1]|argumento 2: %f\n", Op(1)->value.f);
}



