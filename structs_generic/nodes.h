#ifndef node_H
#define node_H

#include "darray.h"

#define NewNodeCode(x,y,z) newNodeCode(x,(Arg)y,(Arg)z)
#define NewNodeOp(x,y) newNodeOp(x,(Value)y)

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


NodeCode newNodeCode(int instruction, Arg a1, Arg a2);

//----------------------------------------------------------------------------------------------------

typedef union value{
    int i;
    float f;
} Value;

typedef struct nodeOp{ 
    char type;
    Value value;
} *NodeOp;

NodeOp newNodeOp(char type, Value v);

//----------------------------------------------------------------------------------------------------



#endif
