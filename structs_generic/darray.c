#include "darray.h"

Darray newDarray(char type, int size){
    Darray da = (Darray)malloc(sizeof(struct darray));
    da->len = 0;
    da->size = size;
    da->type = type;
    da->node = (Node*)malloc(sizeof(union node)*size);

    return da;
}

void addDarray(Darray da, Node n){
    if(da->len == da->size){
        da->size *= 2;
        da->node = (Node*)realloc(da->node, sizeof(union node)*(da->size) );
    }
     da->node[da->len++] = n;
}

int main(){
    /*
    NodeCode n = NewNodeCode(0, "ola\n", 1);
    printf("%s",n->a1.s);
    NodeCode r = NewNodeCode(0, 1, 1);
    printf("%d\n",r->a1.i);
    */
    Darray da = newDarray('c', 1024);

    addDarray(da, NewNodeCode(0,1,1));
    addDarray(da, NewNodeCode(0,2,1));
    addDarray(da, NewNodeCode(0,3,1));
    printf("%d\n",da->node[1].c->a1.i);

}


