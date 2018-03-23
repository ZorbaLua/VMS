%{
#include "structs/code.h"
#include "structs/types.h"
#include <stdio.h>
#include <unistd.h>

#define newCodeElem(x,y1,y2,z1,z2) newCodeElem(x,(Uvalue)y1,y2,(Uvalue)z1,z2)

extern int yylineno;

void yyerror (const char*);
int yylex();
%}

%union{
    int i;
    float f;
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
%token _WRITE
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

%token<i> _INT
%token<f> _FLOAT

%%
Program : Instr Program
        | 
        ;

Instr   :_PUSHI _INT                { addCode(newCodeElem(PUSHI  , $2, INT    , -1, NOTHING)); } 
        |_PUSHF _FLOAT              { addCode(newCodeElem(PUSHF  , $2, FLOAT  , -1, NOTHING)); }	     
        |_START                     { addCode(newCodeElem(START  , -1, NOTHING, -1, NOTHING)); } 
        |_ADD                       { addCode(newCodeElem(ADD    , -1, NOTHING, -1, NOTHING)); }    
        |_WRITE                     { addCode(newCodeElem(WRITE  , -1, NOTHING, -1, NOTHING)); } 
        |_NOT                       { addCode(newCodeElem(NOT    , -1, NOTHING, -1, NOTHING)); }	      
        ;
//|_SUB	     
//|_MUL	     
//|_DIV	     
//|_MOD	     
// _          
// _          
//|_INF	       
//|_INFEQ	     
//|_SUP	       
//|_SUPEQ	     
//|_EQ	        
//|_DIF	       
// _          
//|_FADD	     
//|_FSUB	     
//|_FMUL	     
//|_FDIV	     
// _          
//|_FCOS	     
//|_FSIN	     
//|_FTAN	     
// _          
//|_FINF	      
//|_FINFEQ    
//|_FSUP	      
//|_FSUPEQ    
//|_FEQ	       
//|_FDIF	      
// _          
// _          
//|_PADD	      
//|_CONCAT    
// _          
//|_ALLOC	     
//|_ALLOCN    
//|_FREE	      
// _          
//|_EQUAL	     
// _          
//|_ATOI	     
//|_ATOF	     
//|_ITOF	     
//|_FTOI	     
//|_STRI	     
//|_STRF	     
//|_PUSHN	     
//|_PUSHS	     
//|_PUSHG	     
//|_PUSHL	     
//|_PUSHSP    
//|_PUSHFP    
//|_PUSHGP    
//|_LOAD	      
//|_LOADN	     
//|_DUP	       
//|_DUPN	      
// _          
//|_POP	      
//|_POPN	     
// _          
//|_STOREL    
//|_STOREG    
//|_STORE	     
//|_STOREN    
// _          
//|_CHECK	     
//|_SWAPV	      
//|_READ       
//|_READI      
//|_READF      
//|_READS      
//|_JUMP       
//|_JZ         
//|_PUSHA      
//|_CALL       
//|_RETURN     
//|_NOP        
//|_ERR        
//|_STOP       
//|_LABEL      


%%

void yyerror(const char *s){
    fprintf(stderr , "\e[1mline:%d: \e[31mERRO\e[0m\e[1m: %s\e[0m \n" , yylineno, s);
    _exit(0);
}
