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


%token _ADD _SUB _MUL _DIV _MOD _NOT _INF _INFEQ _SUP _SUPEQ _EQ _DIF _FADD _FSUB _FMUL _FDIV _FCOS _FSIN _FTAN _FINF _FINFEQ _FSUP _FSUPEQ _FEQ _FDIF _PADD _CONCAT _ALLOC _ALLOCN _FREE _EQUAL _ATOI _ATOF _ITOF _FTOI _STRI _STRF _PUSHI _PUSHN _PUSHF _PUSHS _PUSHG _PUSHL _PUSHSP _PUSHFP _PUSHGP _LOAD _LOADN _DUP _DUPN _POP _POPN _STOREL _STOREG _STORE _STOREN _CHECK _SWAP _WRITE _READ _READI _READF _READS _JUMP _JZ _PUSHA _CALL _RETURN _START _NOP _ERR _STOP _LABEL 
%token<i> _INT 
%token<f> _FLOAT
%token<s> _STRING


%%
Program : Program Instr
        | 
        ;

Instr   :_PUSHI _INT    { Code_add( newCodeElem( PUSHI, newValue((Uvalue)$2, T_int)  , newValue((Uvalue)-1, NOTHING) ) ); } 
        |_PUSHF _FLOAT  { Code_add( newCodeElem( PUSHF, newValue((Uvalue)$2, T_float), newValue((Uvalue)-1, NOTHING) ) ); }	     
        |_START         { Code_add( newCodeElem( START, newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); } 
        |_ADD           { Code_add( newCodeElem( ADD  , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }    
        |_WRITE         { Code_add( newCodeElem( WRITE, newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); } 
        |_NOT           { Code_add( newCodeElem( NOT  , newValue((Uvalue)-1, NOTHING), newValue((Uvalue)-1, NOTHING) ) ); }	      
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
