
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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
int gui = 0;
int wp[2];
int rp[2];


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

        case NOT    : semNot();     break;//v 
        case EQUAL  : semEqual();   break;//v

      //-Operacoes Sobre Inteiros----------------------//
        case ADD    : semAdd();     break;//v 
        case SUB    : semSub();     break;//v
        case MUL    : semMul();     break;//v
        case DIV    : semDiv();     break;//v
        case MOD    : semMod();     break;//v

        case INF    : semInf();     break;//v
        case INFEQ  : semInfeq();   break;//v
        case SUP    : semSup();     break;//v
        case SUPEQ  : semSupeq();   break;//v

      //-Operacoes Sobre Flutuantes--------------------//
        case FADD   : semFadd();  	break;//v
        case FSUB   : semFsub();  	break;//v
        case FMUL   : semFmul();  	break;//v
        case FDIV   : semFdiv();  	break;//v

        case FINF   : semFinf();  	break;//v
        case FINFEQ : semFinfeq();  break;//v
        case FSUP   : semFsup();  	break;//v
        case FSUPEQ : semFsupeq();  break;//v

      //-Operacoes Sobre Enderecos---------------------//
        case PADD   : semPadd();  	break;//v
                      
      //-Operacoes Sobre Cadeias de Caracteres---------//
        case CONCAT : semConcat();  break;//x

      //-Operacoes Sobre Heap--------------------------//
        case ALLOC  : semAlloc(f);  break;//v
        case ALLOCN : semAllocn();  break;//v
        case FREE   : semFree();  	break;//x

      //-Conversoes------------------------------------//
        case ATOI   : semAtoi();  	break;//x
        case ATOF   : semAtof();  	break;//x
        case ITOF   : semItof();  	break;//x
        case FTOI   : semFtoi();  	break;//x
        case STRI   : semStri();  	break;//x
        case STRF   : semStrf();  	break;//x

      //-Empilhar--------------------------------------//
        case PUSHI  : semPushi(f);  break;//v
        case PUSHN  : semPushn(f);  break;//v
        case PUSHF  : semPushf(f);  break;//v
        case PUSHS  : semPushs();   break;//x
        case PUSHG  : semPushg(f);  break;//v~
        case PUSHL  : semPushl(f);  break;//v
        case PUSHSP : semPushsp();  break;//v
        case PUSHFP : semPushfp();  break;//v
        case PUSHGP : semPushgp();  break;//v
        case LOAD   : semLoad();  	break;//x
        case LOADN  : semLoadn();   break;//x
        case DUP    : semDup(f);  	break;//v
        case DUPN   : semDupn();  	break;//v

      //-Retirar---------------------------------------//
        case POP    : semPop(f);   	break;//v
        case POPN   : semPopn();  	break;//v

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
    pipe(wp);
    pipe(rp);
    if(!fork()){//parent
        dup2(wp[1], 1); 
    }
    else{//child
        dup2(wp[0], 0);
        dup2(rp[1], 1);
        execlp("interface", "interface", "\0");
        //execvp("interface", NULL);
    }
}

void options(int argc, char** argv){
    int i, j, k, fd;
    if(argc < 2) try(-1);
    for(i=1; i<argc; i++){
        if(argv[i][0] == '-'){
            k=1;
            for(j=1; argv[i][j] != '\0'; j++){
                switch(argv[i][j]){
                    case 's': break; 
                    case 'c': codeSize = atoi(argv[i+k++]); break;
                    case 'o': opSize   = atoi(argv[i+k++]); break;
                    case 'C': callSize = atoi(argv[i+k++]); break;
                    case 'h': heapSize = atoi(argv[i+k++]); break;
                    case 'g': gui = 1; execGui();           break;
                }
            }
            i += k-1;
        }
        else{
            fd = open(argv[i], O_RDONLY);
            dup2(fd, 0);
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
    if(gui) dup2(rp[0], 0);
    runProgram();

    _exit(0);
}
