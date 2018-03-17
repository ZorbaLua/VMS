#include <stdlib.h>
#include "nodes.h"

NodeCode newNodeCode(int instruction, Arg a1, Arg a2){
    NodeCode nc = (NodeCode)malloc(sizeof(struct nodeCode));

    nc->instruction = instruction;
    nc->a1 = a1;
    nc->a2 = a2;

    return nc;
}

NodeOp newNodeOp(char type, Value value){
    NodeOp no = (NodeOp)malloc(sizeof(struct nodeOp));
    
    no->value = value;
    no->type = type;

    return no;
}






