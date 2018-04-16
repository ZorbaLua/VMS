#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "semantic.h"
#include "structs/code.h"
#include "structs/opStack.h"
#include "structs/callStack.h"
#include "structs/heap.h"

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

extern FILE* yyin;
GHashTable* labels = NULL;
Code code;
OpStack opstack;
CallStack callstack;
Heap heap;
int codeSize = 10000;
int opSize   = 1000;
int callSize = 100;
int heapSize = 1000;
int gui = 0;
pid_t pidGui;


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
        case SWAP   : semSwap();  	break;//v

      //-Input/Output----------------------------------//
        case WRITE  : semWrite();   break;//x
        case READ   : semRead();  	break;//x

      //-Registo PC------------------------------------//
        case JUMP   : semJump(f);  	break;//v
        case JZ     : semJz(f);    	break;//v
        case PUSHA  : semPusha(f);  break;//v

      //-Procedimentos---------------------------------//
        case CALL   : semCall();  	break;//v
        case RETURN : semReturn();  break;//v

      //-Inicializacao e Fim---------------------------//
        case START  : semStart();   break;//v
        case STOP   :               break;//v
        case NOP    : semNop();   	break;//v
        case ERR    : semErr();   	break;//x
    }
}

void runProgram(){
    CodeElem ce;
    char str[MAX_LINE];
    int stop = 0, nInst=0, i=0;
    while(1){
        write(1, "inst:\n", 6);
        fgets(str, MAX_LINE, stdin);
        if(str[0]<'0' || str[0]>'9'){
            // limpar estruturas
            if((yyin = fopen(str, "r"))<0) try(1);
            yyparse();
        }
        else{
            i=0;
            nInst = atoi(str);
            while( i<nInst && !Code_get(&ce) && !stop ){
                if(ce->inst == STOP) stop = 1;
                printCode(ce, '_', code.pc);
                runInst(ce);
                i++;
            }
        }
    }
}

void execGui(){
    int wp[2], rp[2], len;
    char filename[MAX_LINE];
    if (pipe(wp)<0 || pipe(rp)<0) try(1);
    if( (pidGui=fork()) ){//parent
        close(wp[0]);
        close(rp[1]);
        dup2(wp[1], 1); 
        dup2(rp[0], 0);
        fgets(filename, MAX_LINE, stdin);
        len = strnlen(filename, MAX_LINE);
        filename[len-1] = '\0';
        if((yyin = fopen(filename, "r"))<0) try(1);
    }
    else{//child
        close(wp[1]);
        close(rp[0]);
        dup2(wp[0], 0);
        dup2(rp[1], 1);
        execlp("./interface", "./interface", NULL);
    }
}

void options(int argc, char** argv){// debug
    int i, j, k;
    if(argc < 2) try(-1);
    for(i=1; i<argc; i++){
        if(argv[i][0] == '-'){
            k=1;
            for(j=1; argv[i][j] != '\0'; j++){
                switch(argv[i][j]){
                    case 's': break; 
                    case 'c': codeSize = atoi(argv[i+k]);k++; break;
                    case 'o': opSize   = atoi(argv[i+k]);k++; break;
                    case 'C': callSize = atoi(argv[i+k]);k++; break;
                    case 'h': heapSize = atoi(argv[i+k]);k++; break;
                    case 'g': execGui(); gui = 1;           break;
                }
                i += k-1;
            }
        }
        else if(!gui) if((yyin = fopen(argv[i], "r"))<0) try(1);
    }
}

void finish(){
    close(0);
    close(1);
    kill(pidGui, SIGKILL);
}

void signals(){
    signal(SIGKILL, finish);
    signal(SIGQUIT, finish);
    signal(SIGSEGV, finish);
}

int main(int argc, char** argv){
    signals();
    options(argc, argv);
    Code_init(codeSize);
    OpStack_init(opSize);
    CallStack_init(callSize);
    Heap_init(heapSize);
    labels = g_hash_table_new(g_str_hash, g_str_equal);

    yyparse();
    runProgram();

    return 0;
}
