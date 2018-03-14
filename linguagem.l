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

"ADD"   { return ADD; }
"SUB"   { return SUB; }
"MUL"   { return MUL; }
"DIV"   { return DIV; }
"MOD"   { return MOD; }

"NOT"   { return NOT; } // Duvida

"INF"   { return INF;   }
"INFEQ" { return INFEQ; }
"SUP"   { return SUP;   }
"SUPEQ" { return SUPEQ; }
"EQ"    { return EQ;    } // ?
"DIF"   { return DIF;   } // ?

  //-Operacoes Sobre Flutuantes--------------------//

"FADD"   { return FADD; }
"FSUB"   { return FSUB; }
"FMUL"   { return FMUL; }
"FDIV"   { return FDIV; }

"FCOS"   { return FCOS; }
"FSIN"   { return FSIN; }
"FTAN"   { return FTAN; } // ?

"FINF"   { return FINF;   }
"FINFEQ" { return FINFEQ; }
"FSUP"   { return FSUP;   }
"FSUPEQ" { return FSUPEQ; }
"FEQ"    { return FEQ;    } // ?
"FDIF"   { return FDIF;   } // ?

  //-Operacoes Sobre Enderecos---------------------//

"PADD"   { return PADD;   }
"CONCAT" { return CONCAT; }

  //-Operacoes Sobre Cadeias de Caracteres---------//

"ALLOC"  { return ALLOC;  }
"ALLOCN" { return ALLOCN; }
"FREE"   { return FREE;   }

  //-Igualdade-------------------------------------//

"EQUAL"  { return EQUAL; }

  //-Conversoes------------------------------------//

"ATOI"   { return ATOI; }
"ATOF"   { return ATOF; }
"ITOF"   { return ITOF; }
"FTOI"   { return FTOI; }
"STRI"   { return STRI; }
"STRF"   { return STRF; }

  //-Empilhar--------------------------------------//

"PUSHI"  { return PUSHI;  }
"PUSHN"  { return PUSHN;  }
"PUSHF"  { return PUSHF;  }
"PUSHS"  { return PUSHS;  }
"PUSHG"  { return PUSHG;  }
"PUSHL"  { return PUSHL;  }
"PUSHSP" { return PUSHSP; }
"PUSHFP" { return PUSHFP; }
"PUSHGP" { return PUSHGP; }
"LOAD"   { return LOAD;   }
"LOADN"  { return LOADN;  }
"DUP"    { return DUP;    }
"DUPN"   { return DUPN;   }

  //-Retirar---------------------------------------//

"POP"  { return POP;  }
"POPN" { return POPN; }

  //-Arquivar--------------------------------------//

"STOREL" { return STOREL; }
"STOREG" { return STOREG; }
"STORE"  { return STORE;  }
"STOREN" { return STOREN; }

  //-Diversos--------------------------------------//

"CHECK" { return CHECK; }
"SWAP"  { return SWAP;  }

  //-Input/Output----------------------------------//

"WRITEI" { return WRITEI; }
"WRITEF" { return WRITEF; }
"WRITES" { return WRITES; }

"READ"   { return READ;   }

"READI"  { return READI;  } // ?
"READF"  { return READF;  } // ?
"READS"  { return READS;  } // ?

  //-Primitivas Graficas---------------------------//

    // Apartida Nada

  //-Registo PC------------------------------------//

"JUMP"  { return JUMP;  }
"JZ"    { return JZ;    }
"PUSHA" { return PUSHA; }

  //-Procedimentos---------------------------------//

"CALL"   { return CALL;   }
"RETURN" { return RETURN; }

  //-Inicializacao e Fim---------------------------//

"START" { return START; }
"NOP"   { return NOP;   }
"ERR"   { return ERR;   }
"STOP"  { return STOP;  }

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
