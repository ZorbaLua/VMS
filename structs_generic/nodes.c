#include "nodes.h"

Node newNodeCode(int instruction, Arg a1, Arg a2){
    NodeCode nc = (NodeCode)malloc(sizeof(struct nodeCode));

    nc->instruction = instruction;
    nc->a1 = a1;
    nc->a2 = a2;

    return (Node)nc;
}






