#include "darray.h"

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#define Code1(i) da->node[i].c->a1
#define Code2(i) da->node[i].c->a2

#define addCode(...) addDarray(da, NewNodeCode(__VA_ARGS__))


int main(){
    Darray da = newDarray('c', 1024);

    //addDarray(da, NewNodeCode(0,2,1));
    addCode(0,1,1);
    addCode(0,"ola",1);
    addCode(0,2,"tudo");
    printf("%s\n", Code1(1).s);

}



