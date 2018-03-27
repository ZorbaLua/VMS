
#include <stdio.h>
#include <unistd.h>

#include "semantic.h"

#include "structs/code.h"
#include "structs/opStack.h"
#include "structs/callStack.h"
#include "structs/heap.h"

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

Code code;
OpStack opstack;
CallStack callstack;
Heap heap;
int codeSize = 10000;
int opSize   = 1000;
int callSize = 100;
int heapSize = 1000;


int yyparse();

void try(int erro) {
    switch (erro) {
        case  0: return;
        case -1: eprintf("Missing input file\n");                           break;
        case -2: eprintf("Aritmetic operation mod only defined to int\n");  break;
    }
    _exit(erro);
}

void runInst(CodeElem ce){
    Value f = ce->first;
    //Value s = ce->second;

    switch(ce->inst){

      //-Operacoes Sobre Inteiros----------------------//
        case ADD    : semAdd();     break;//x 
        case SUB    : semSub();     break;//x
        case MUL    : semMul();     break;//x
        case DIV    : semDiv();     break;//x
        case MOD    : semMod();     break;//x

        case NOT    : semNot();     break;//x 

        case INF    : semInf();     break;//x
        case INFEQ  : semInfeq();   break;//x
        case SUP    : semSup();     break;//x
        case SUPEQ  : semSupeq();   break;//x
        case EQ	    : semEq();      break;//x
        case DIF    : semDif();     break;//x

      //-Operacoes Sobre Flutuantes--------------------//
        case FADD   : semFadd();  	break;//x
        case FSUB   : semFsub();  	break;//x
        case FMUL   : semFmul();  	break;//x
        case FDIV   : semFdiv();  	break;//x

        case FCOS   : semFcos();  	break;//x
        case FSIN   : semFsin();  	break;//x
        case FTAN   : semFtan();  	break;//x

        case FINF   : semFinf();  	break;//x
        case FINFEQ : semFinfeq();  break;//x
        case FSUP   : semFsup();  	break;//x
        case FSUPEQ : semFsupeq();  break;//x
        case FEQ    : semFeq();   	break;//x
        case FDIF   : semFdif();  	break;//x

      //-Operacoes Sobre Enderecos---------------------//
        case PADD   : semPadd();  	break;//x
                      
      //-Operacoes Sobre Cadeias de Caracteres---------//
        case CONCAT : semConcat();  break;//x

      //-Operacoes Sobre Heap--------------------------//
        case ALLOC  : semAlloc();   break;//x
        case ALLOCN : semAllocn();  break;//x
        case FREE   : semFree();  	break;//x

      //-Igualdade-------------------------------------//
        case EQUAL  : semEqual();   break;//x

      //-Conversoes------------------------------------//
        case ATOI   : semAtoi();  	break;//x
        case ATOF   : semAtof();  	break;//x
        case ITOF   : semItof();  	break;//x
        case FTOI   : semFtoi();  	break;//x
        case STRI   : semStri();  	break;//x
        case STRF   : semStrf();  	break;//x

      //-Empilhar--------------------------------------//
        case PUSHI  : semPushi(f);  break;//v
        case PUSHN  : semPushn();   break;//x
        case PUSHF  : semPushf(f);  break;//v
        case PUSHS  : semPushs();   break;//x
        case PUSHG  : semPushg();   break;//x
        case PUSHL  : semPushl();   break;//x
        case PUSHSP : semPushsp();  break;//x
        case PUSHFP : semPushfp();  break;//x
        case PUSHGP : semPushgp();  break;//x
        case LOAD   : semLoad();  	break;//x
        case LOADN  : semLoadn();   break;//x
        case DUP    : semDup();  	break;//x
        case DUPN   : semDupn();  	break;//x

      //-Retirar---------------------------------------//
        case POP    : semPop();   	break;//x
        case POPN   : semPopn();  	break;//x

      //-Arquivar--------------------------------------//
        case STOREL : semStorel();  break;//x
        case STOREG : semStoreg();  break;//x
        case STORE  : semStore();   break;//x
        case STOREN : semStoren();  break;//x

      //-Diversos--------------------------------------//
        case CHECK  : semCheck();   break;//x
        case SWAP   : semSwap();  	break;//x

      //-Input/Output----------------------------------//
        case WRITE  : semWrite();   break;//x
        case READ   : semRead();  	break;//x

      //-Registo PC------------------------------------//
        case JUMP   : semJump();  	break;//x
        case JZ     : semJz();    	break;//x
        case PUSHA  : semPusha();   break;//x

      //-Procedimentos---------------------------------//
        case CALL   : semCall();  	break;//x
        case RETURN : semReturn();  break;//x

      //-Inicializacao e Fim---------------------------//
        case START  : semStart();   break;//x
        case NOP    : semNop();   	break;//x
        case ERR    : semErr();   	break;//x
        case STOP   : semStop();  	break;//x

      //-Extra-----------------------------------------//
        case LABEL  : semLabel();   break;//x
    }
}

void runProgram(){
    CodeElem ce;
    while( !Code_get(&ce)){
        printCode(ce, ' ');
        runInst(ce);
    }
}

void execGui(){
    int d[2];
    pipe(d);
    if(!fork()){//parent
        
    }
    else{
        execvp("interface", NULL);
    }
}

void options(int argc, char** argv){
    int i, j, k;
    if(argc < 2) try(-1);
    for(i=1; i<argc; i++){
        if(argv[i][0] == '-'){
            k=1;
            for(j=1; argv[i][j] != '\0'; j++){
                switch(argv[i][j]){
                    case 's': break; 
                    case 'c': codeSize = atoi(argv[i+k++]); break;
                    case 'o': opSize = atoi(argv[i+k++]);   break;
                    case 'C': callSize = atoi(argv[i+k++]); break;
                    case 'h': heapSize = atoi(argv[i+k++]); break;
                    case 'g': execGui();                    break;
                }
            }
        }
    }
}

int main(int argc, char** argv){
    options(argc, argv);
    Code_init(codeSize);
    OpStack_init(opSize);
    CallStack_init(callSize);
    Heap_init(heapSize);


    yyparse();
    runProgram();

    _exit(0);
}
