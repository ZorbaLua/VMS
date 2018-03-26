
#include <stdio.h>
#include <unistd.h>

#include "semantic.h"

#include "structs/code.h"
#include "structs/opStack.h"
#include "structs/callStack.h"

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

Code code;
OpStack opstack;
CallStack callstack;

int yyparse();

void try (int erro) {
    switch (erro) {
        case 0: return;
        case -2: eprintf("Aritmetic operation mod only defined to int\n");
    }
    _exit(-1);
}

void runInst(CodeElem ce){
    Value f = ce->first;
    //Value s = ce->second;

    switch(ce->inst){

      //-Operacoes Sobre Inteiros----------------------//
        case ADD    : semAdd();     break;
        case SUB    : semSub();     break;
        case MUL    : semMul();     break;
        case DIV    : semDiv();     break;
        case MOD    : semMod();     break;

        case NOT    : semNot();     break; 

        case INF    : semInf();     break;
        case INFEQ  : semInfeq();   break;
        case SUP    : semSup();     break;
        case SUPEQ  : semSupeq();   break;
        case EQ	    : semEq();      break;
        case DIF    : semDif();     break;

      //-Operacoes Sobre Flutuantes--------------------//
        case FADD   : semFadd();  	break;
        case FSUB   : semFsub();  	break;
        case FMUL   : semFmul();  	break;
        case FDIV   : semFdiv();  	break;

        case FCOS   : semFcos();  	break;
        case FSIN   : semFsin();  	break;
        case FTAN   : semFtan();  	break;

        case FINF   : semFinf();  	break;
        case FINFEQ : semFinfeq();  break;
        case FSUP   : semFsup();  	break;
        case FSUPEQ : semFsupeq();  break;
        case FEQ    : semFeq();   	break;
        case FDIF   : semFdif();  	break;

      //-Operacoes Sobre Enderecos---------------------//
        case PADD   : semPadd();  	break;
        case CONCAT : semConcat();  break;

      //-Operacoes Sobre Cadeias de Caracteres---------//
        case ALLOC  : semAlloc();   break;
        case ALLOCN : semAllocn();  break;
        case FREE   : semFree();  	break;

      //-Igualdade-------------------------------------//
        case EQUAL  : semEqual();   break;

      //-Conversoes------------------------------------//
        case ATOI   : semAtoi();  	break;
        case ATOF   : semAtof();  	break;
        case ITOF   : semItof();  	break;
        case FTOI   : semFtoi();  	break;
        case STRI   : semStri();  	break;
        case STRF   : semStrf();  	break;

      //-Empilhar--------------------------------------//
        case PUSHI  : semPushi(f);  break;//
        case PUSHN  : semPushn();   break;
        case PUSHF  : semPushf(f);  break;//
        case PUSHS  : semPushs();   break;
        case PUSHG  : semPushg();   break;
        case PUSHL  : semPushl();   break;
        case PUSHSP : semPushsp();  break;
        case PUSHFP : semPushfp();  break;
        case PUSHGP : semPushgp();  break;
        case LOAD   : semLoad();  	break;
        case LOADN  : semLoadn();   break;
        case DUP    : semDup();  	break;
        case DUPN   : semDupn();  	break;

      //-Retirar---------------------------------------//
        case POP    : semPop();   	break;
        case POPN   : semPopn();  	break;

      //-Arquivar--------------------------------------//
        case STOREL : semStorel();  break;
        case STOREG : semStoreg();  break;
        case STORE  : semStore();   break;
        case STOREN : semStoren();  break;

      //-Diversos--------------------------------------//
        case CHECK  : semCheck();   break;
        case SWAP   : semSwap();  	break;

      //-Input/Output----------------------------------//
        case WRITE  : semWrite();   break;
        case READ   : semRead();  	break;

      //-Registo PC------------------------------------//
        case JUMP   : semJump();  	break;
        case JZ     : semJz();    	break;
        case PUSHA  : semPusha();   break;

      //-Procedimentos---------------------------------//
        case CALL   : semCall();  	break;
        case RETURN : semReturn();  break;

      //-Inicializacao e Fim---------------------------//
        case START  : semStart();   break;
        case NOP    : semNop();   	break;
        case ERR    : semErr();   	break;
        case STOP   : semStop();  	break;

      //-Extra-----------------------------------------//
        case LABEL  : semLabel();   break;
    }
}

void runProgram(){
    CodeElem ce;
    while( !Code_get(&ce)){
        printf("ola\n");
        printCode(ce, ' ');
        runInst(ce);
    }
}


int main(){
    Code_init(1024);
    OpStack_init(1024);
    CallStack_init(100);


    yyparse();
    runProgram();

    return 0;
}
