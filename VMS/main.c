#include <stdio.h>

#include "semantic.h"
#include "y.tab.h"

#include "structs/code.h"
#include "structs/opStack.h"


// var globais
Code code;
OpStack opStack;

void runInst(){
    CodeElem ce = getCode();
    switch(ce->inst){
        case START: printf("start"); break;
        case PUSHI: semPushi(ce->first); break;
    }
}

void runProgram(){
    while(code.pc!=code.array->len && getCode()->inst!=STOP){
        runInst();
    }
}

void vmsInit(){
    codeInit(1024);
    opStackInit(1024);
}

int main(){
    vmsInit();
    yylex();
    
    runProgram();

    return 0;
}



