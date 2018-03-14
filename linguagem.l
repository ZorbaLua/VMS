%{
#include "linguagem.h"

/* Declaracoes C diversas */
#include "y.tab.h"

%}

%option noyywrap
%option nounput
%option noinput
%option yylineno

%%

  // Operacoes com "?" nao estao na VMS anterior

  //-Operacoes Sobre Inteiros----------------------//

"ADD"   { yylval.cha = '+'; return OSP; }
"SUB"   { yylval.cha = '-'; return OSP; }
"MUL"   { yylval.cha = '*'; return OCP; }
"DIV"   { yylval.cha = '/'; return OCP; }
"MOD"   { yylval.cha = '%'; return OCP; }

"NOT"   { yylval.cha = 'z'; return OSP; } // Duvida

"INF"   { yylval.cha = 'l'; return REL; }
"INFEQ" { yylval.cha = 'L'; return REL; }
"SUP"   { yylval.cha = 'g'; return REL; }
"SUPEQ" { yylval.cha = 'G'; return REL; }
"EQ"    { yylval.cha = 'e'; return REL; } // ?
"DIF"   { yylval.cha = 'n'; return REL; } // ?

  //-Operacoes Sobre Flutuantes--------------------//

"FADD"   { yylval.cha = '+'; return FOSP; }
"FSUB"   { yylval.cha = '-'; return FOSP; }
"FMUL"   { yylval.cha = '*'; return FOCP; }
"FDIV"   { yylval.cha = '/'; return FOCP; }

"FCOS"   { yylval.cha = 'c'; return FOP; }
"FSIN"   { yylval.cha = 's'; return FOP; }
"FTAN"   { yylval.cha = 't'; return FOP; } // ?

"FINF"   { yylval.cha = 'l'; return FREL; }
"FINFEQ" { yylval.cha = 'L'; return FREL; }
"FSUP"   { yylval.cha = 'g'; return FREL; }
"FSUPEQ" { yylval.cha = 'G'; return FREL; }
"FEQ"    { yylval.cha = 'e'; return FREL; } // ?
"FDIF"   { yylval.cha = 'n'; return FREL; } // ?

  //-Operacoes Sobre Enderecos---------------------//

"PADD"   { yylval.cha = 'p'; return ED; }
"CONCAT" { yylval.cha = 'c'; return ED; }

  //-Operacoes Sobre Cadeias de Caracteres---------//

"ALLOC"  { yylval.cha = 'a'; return HEAP; }
"ALLOCN" { yylval.cha = 'n'; return HEAP; }
"FREE"   { yylval.cha = 'f'; return HEAP; }

  //-Igualdade-------------------------------------//

"EQUAL"  { yylval.cha = 'e'; return REL; }

  //-Conversoes------------------------------------//

"ATOI"   { yylval.cha = 'f'; return CONV; }
"ATOF"   { yylval.cha = 'f'; return CONV; }
"ITOF"   { yylval.cha = 'f'; return CONV; }
"FTOI"   { yylval.cha = 'f'; return CONV; }
"STRI"   { yylval.cha = 'f'; return CONV; }
"STRF"   { yylval.cha = 'f'; return CONV; }

  //-Empilhar--------------------------------------//

"PUSHI"  { yylval.cha = 'f'; return EMP; }
"PUSHN"  { yylval.cha = 'f'; return EMP; }
"PUSHF"  { yylval.cha = 'f'; return EMP; }
"PUSHS"  { yylval.cha = 'f'; return EMP; }
"PUSHG"  { yylval.cha = 'f'; return EMP; }
"PUSHL"  { yylval.cha = 'f'; return EMP; }
"PUSHSP" { yylval.cha = 'f'; return EMP; }
"PUSHFP" { yylval.cha = 'f'; return EMP; }
"PUSHGP" { yylval.cha = 'f'; return EMP; }
"LOAD"   { yylval.cha = 'f'; return EMP; }
"LOADN"  { yylval.cha = 'f'; return EMP; }
"DUP"    { yylval.cha = 'f'; return EMP; }
"DUPN"   { yylval.cha = 'f'; return EMP; }

  //-Retirar---------------------------------------//

"POP"  { yylval.cha = 'f'; return RET; }
"POPN" { yylval.cha = 'f'; return RET; }

  //-Arquivar--------------------------------------//

"STOREL" { yylval.cha = 'f'; return STORE; }
"STOREG" { yylval.cha = 'f'; return STORE; }
"STORE"  { yylval.cha = 'f'; return STORE; }
"STOREN" { yylval.cha = 'f'; return STORE; }

  //-Diversos--------------------------------------//

"CHECK" {                    return CHECK; }
"SWAP"  {                    return SWAP;  }

  //-Input/Output----------------------------------//

"WRITEI" { yylval.cha = 'i'; return WRITE; }
"WRITEF" { yylval.cha = 'f'; return WRITE; }
"WRITES" { yylval.cha = 's'; return WRITE; }

"READ"   {                   return READ; }

"READI"  { yylval.cha = 'i'; return READ; } // ?
"READF"  { yylval.cha = 'f'; return READ; } // ?
"READS"  { yylval.cha = 's'; return READ; } // ?

  //-Primitivas Graficas---------------------------//

    // Apartida Nada

  //-Registo PC------------------------------------//

"JUMP"  { yylval.cha = 'f'; return PC; }
"JZ"    { yylval.cha = 'f'; return PC; }
"PUSHA" { yylval.cha = 'f'; return PC; }

  //-Procedimentos---------------------------------//

"CALL"   {                  return CALL; }
"RETURN" {                  return RETURN; }

  //-Inicializacao e Fim---------------------------//

"START" {                   return START; }
"NOP"   {                   return NOP; }
"ERR"   {                   return ERR; }
"STOP"  {                   return STOP; }

  //-Resto----------------------------------------//

-?[0-9]+"."[0-9]+ { yylval.fl = atof(yytext);      return FLOAT; }
-?[0-9]+				  { yylval.integer = atoi(yytext); return INT; }
\"(\\.|[^"\\])*\" { yylval.string = GSN(yytext);   return STRING; }

[a-z][a-zA-Z0-9]* { yylval.string = GSN(yytext);   return ID; }

[\[\](){}=;,]     { return yytext[0]; }

[ \t\n]*          { ; }
"//".*            { ; }
.                 { GString *erro = GSN(""); GSAP(erro,"\e[1minvalid char: \"%s\"\e[0m\n", yytext); yyerror(erro->str); }

%%
