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


"int"                       { yylval.cha = 'i';                     return TINT; }
"float"                     { yylval.cha = 'f';                     return TFLOAT;}
"void"                      { yylval.cha = 'v';                     return VOID; }

"if"                        {                                       return IF; }
"else"                      {                                       return ELSE; }
"while"                     {                                       return WHILE; }
"for"                       {                                       return FOR; }
"in"                        {                                       return IN; }
"return"                    {                                       return RET; }

"def"                       {                                       return DEF; /* def e call nao sao necessarios com lookahaed(yychar)*/}
"call"                      {                                       return CALL;}

"writei"                    { yylval.cha = 'i';                     return WRITE; }
"writef"                    { yylval.cha = 'f';                     return WRITE; }
"writes"                    { yylval.cha = 's';                     return WRITE; }

"readi"                     { yylval.cha = 'i';                     return READ; }
"readf"                     { yylval.cha = 'f';                     return READ; }
"reads"                     { yylval.cha = 's';                     return READ; }

"or"                        { yylval.cha = 'o';                     return OL; }
"and"                       { yylval.cha = 'a';                     return OL; }
"true"                      { yylval.string = GSN("pushi 1\n");     return BOOL; }
"false"                     { yylval.string = GSN("pushi 0\n");     return BOOL; }

"*"                         { yylval.cha = '*';                     return OCP; }
"/"                         { yylval.cha = '/';                     return OCP; }
"%"                         { yylval.cha = '%';                     return OCP; }
"+"                         { yylval.cha = '+';                     return OSP; }
"-"                         { yylval.cha = '-';                     return OSP; }

-?[0-9]+"."[0-9]+			{ yylval.fl = atof(yytext);             return FLOAT; }
-?[0-9]+					{ yylval.integer = atoi(yytext);        return INT; }
\"(\\.|[^"\\])*\"           { yylval.string = GSN(yytext);          return STRING; }
 
[a-z][a-zA-Z0-9]*           { yylval.string = GSN(yytext);          return ID; }
  
"<"                         { yylval.cha = 'l';                     return REL;}
">"                         { yylval.cha = 'g';                     return REL; }
"<="                        { yylval.cha = 'L';                     return REL; }
">="                        { yylval.cha = 'G';                     return REL; }
"=="                        { yylval.cha = 'e';                     return REL; }
"!="                        { yylval.cha = 'n';                     return REL; }

[\[\](){}=;,]               { return yytext[0]; }

[ \t\n]*                    { ; }
"//".*                      { ; }
 
.                           { GString *erro = GSN(""); GSAP(erro,"\e[1minvalid char: \"%s\"\e[0m\n", yytext); yyerror(erro->str);}
%%


