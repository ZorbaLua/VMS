#include "array.h"

CodeStack newCodeStack(int size){
    CodeStack cs = (CodeStack)malloc(sizeof(struct codeStack));
    cs->len = 0;
    cs->size = size;
    cs->nc = (NodeCode*)malloc(sizeof(struct nodeCode)*size);

    return cs;
}

void addCodeStack(CodeStack cs,NodeCode n){
    if(cs->len == cs->size){
        cs->size *= 2;
        cs->nc = (NodeCode*)realloc(cs->nc, sizeof(struct nodeCode)*(cs->size) );
    }
     cs->nc[cs->len++] = n;
}

int main(){
    /*
    NodeCode n = NewNodeCode(0, "ola\n", 1);
    printf("%s",n->a1.s);
    NodeCode r = NewNodeCode(0, 1, 1);
    printf("%d\n",r->a1.i);
    */
    CodeStack cs = newCodeStack(1024);

    addCodeStack(cs, NewNodeCode(0,1,1));
    addCodeStack(cs, NewNodeCode(0,2,1));
    addCodeStack(cs, NewNodeCode(0,3,1));
    printf("%d\n",cs->nc[1]->a1);
}


