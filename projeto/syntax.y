%{
#include <stdio.h>
#include <unistd.h>
#include <glib.h>
#include "structs/code.h"
#include "structs/types.h"

extern int yylineno;
extern Code code;

void yyerror (const char*);
void add(CodeElem);
int yylex();
%}

%union{
    int i; 
    float f;
    GString* s;
}


%token _ADD _SUB _MUL _DIV _MOD _NOT _INF _INFEQ _SUP _SUPEQ _FADD _FSUB _FMUL _FDIV _FINF _FINFEQ _FSUP _FSUPEQ _PADD _CONCAT _ALLOC _ALLOCN _FREE _EQUAL _ATOI _ATOF _ITOF _FTOI _STRI _STRF _PUSHI _PUSHN _PUSHF _PUSHS _PUSHG _PUSHL _PUSHSP _PUSHFP _PUSHGP _LOAD _LOADN _DUP _DUPN _POP _POPN _STOREL _STOREG _STORE _STOREN _CHECK _SWAP _WRITE _READ _READI _READF _READS _JUMP _JZ _PUSHA _CALL _RETURN _START _NOP _ERR _STOP _LABEL 
%token<i> _INT 
%token<f> _FLOAT
%token<s> _STRING


%%
Program : Program Instr
        | 
        ;

Instr   :_PUSHI _INT    { Code_add( newCodeElem( PUSHI , newValue((Uvalue)$2, T_int)  , newValue((Uvalue)-1, NOTHING) ) ); } 
        |_PUSHF _FLOAT  { Code_add( newCodeElem( PUSHF , newValue((Uvalue)$2, T_float), newValue((Uvalue)-1, NOTHING) ) ); }	     
        |_START         { Code_add( newCodeElem( START , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); } 
        |_ADD           { Code_add( newCodeElem( ADD   , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }    
        |_WRITE         { Code_add( newCodeElem( WRITE , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); } 
        |_NOT           { Code_add( newCodeElem( NOT   , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }	      
        |_SUB	        { Code_add( newCodeElem( SUB   , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_MUL	        { Code_add( newCodeElem( MUL   , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_DIV	        { Code_add( newCodeElem( DIV   , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_MOD	        { Code_add( newCodeElem( MOD   , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_INF	        { Code_add( newCodeElem( INF   , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_INFEQ	        { Code_add( newCodeElem( INFEQ , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_SUP	        { Code_add( newCodeElem( SUP   , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_SUPEQ	        { Code_add( newCodeElem( SUPEQ , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_FADD	        { Code_add( newCodeElem( FADD  , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_FSUB	        { Code_add( newCodeElem( FSUB  , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_FMUL	        { Code_add( newCodeElem( FMUL  , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_FDIV	        { Code_add( newCodeElem( FDIV  , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_FINF	        { Code_add( newCodeElem( FINF  , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_FINFEQ        { Code_add( newCodeElem( FINFEQ, newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_FSUP	        { Code_add( newCodeElem( FSUP  , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_FSUPEQ        { Code_add( newCodeElem( FSUPEQ, newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        |_EQUAL         { Code_add( newCodeElem( EQUAL , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }
        ;
// _          
// _          
//|_PADD	      
//|_CONCAT    
// _          
//|_ALLOC	     
//|_ALLOCN    
//|_FREE	      
// _          
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
