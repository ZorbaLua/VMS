%{
#include "semantic.h"
#include "structs/types.h"
#include "structs/code.h"


void yyerror (const char*);
%}

%union{
    Value v;
}


%token _ADD
%token _SUB
%token _MUL
%token _DIV
%token _MOD
%token _NOT
%token _INF
%token _INFEQ
%token _SUP
%token _SUPEQ
%token _EQ
%token _DIF
%token _FADD
%token _FSUB
%token _FMUL
%token _FDIV
%token _FCOS
%token _FSIN
%token _FTAN

%token _FINF
%token _FINFEQ
%token _FSUP
%token _FSUPEQ
%token _FEQ
%token _FDIF
%token _PADD
%token _CONCAT
%token _ALLOC
%token _ALLOCN
%token _FREE
%token _EQUAL
%token _ATOI
%token _ATOF
%token _ITOF
%token _FTOI

%token _STRI
%token _STRF
%token _PUSHI
%token _PUSHN
%token _PUSHF
%token _PUSHS
%token _PUSHG
%token _PUSHL
%token _PUSHSP
%token _PUSHFP
%token _PUSHGP
%token _LOAD
%token _LOADN
%token _DUP
%token _DUPN

%token _POP
%token _POPN
%token _STOREL
%token _STOREG
%token _STORE
%token _STOREN
%token _CHECK
%token _SWAP
%token _WRITEI
%token _WRITEF
%token _WRITES
%token _READ
%token _READI
%token _READF

%token _READS
%token _JUMP
%token _JZ
%token _PUSHA
%token _CALL
%token _RETURN
%token _START
%token _NOP
%token _ERR
%token _STOP

%token _LABEL
%token _STRING

%token<Value> _INT
%token<Value> _FLOAT

%%
//Add: 
//Sub: 
//Mul: 
//Div: 
//Mod: 
//       
//Not:  
//       
//Inf:   
//Infeq: 
//Sup:   
//Supeq: 
//Eq:    
//Dif:   
//       
//Fadd: 
//Fsub: 
//Fmul: 
//Fdiv: 
//       
//Fcos: 
//Fsin: 
//Ftan: 
//       
//Finf:  
//Finfeq:
//Fsup:  
//Fsupeq:
//Feq:   
//Fdif:  
//       
//       
//Padd:  
//Concat:
//       
//Alloc: 
//Allocn:
//Free:  
//       
//Equal: 
//       
//Atoi: 
//Atof: 
//Itof: 
//Ftoi: 
//Stri: 
//Strf: 
       
Pushi: _PUSHI _INT                {addCode(PUSHI, $2, -1, NOTHING);} 
     ;
//Pushn: 
//Pushf: 
//Pushs: 
//Pushg: 
//Pushl: 
//Pushsp:
//Pushfp:
//Pushgp:
//Load:  
//Loadn: 
//Dup:   
//Dupn:  
//       
//Pop:  
//Popn: 
//       
//Storel:
//Storeg:
//Store: 
//Storen:
//       
//Check: 
//Swapv:  


%%


