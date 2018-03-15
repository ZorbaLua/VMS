#ifndef node_H
#define node_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NewNodeCode(x,y,z) newNodeCode(x,(Arg)y,(Arg)z)

typedef union arg{
    int i;
    float f;
    char* s;
} Arg;

typedef struct nodeCode{
    int instruction;
    Arg a1;
    Arg a2;
} *NodeCode;

//----------------------------------------------------------------------------------------------------

typedef union value{
    int i;
    float f;
} Value;

typedef struct nodeOpStack{ 
    Value value;
    char type;
} *NodeOpStack;

//----------------------------------------------------------------------------------------------------

typedef union node{
    NodeCode c;
    NodeOpStack ops;
} Node;


Node newNodeCode(int instruction, Arg a1, Arg a2);

#endif
