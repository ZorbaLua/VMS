%{
#include <unistd.h>
#include "y.tab.h"
%}

%option noyywrap
%option nounput
%option noinput
%option yylineno
%option caseless

%%

"add"    { return _ADD; }
"sub"    { return _SUB; }
"mul"    { return _MUL; }
"div"    { return _DIV; }
"mod"    { return _MOD; }

"not"    { return _NOT; }

"inf"    { return _INF;   }
"infeq"  { return _INFEQ; }
"sup"    { return _SUP;   }
"supeq"  { return _SUPEQ; }
"eq"     { return _EQ;    } // ?
"dif"    { return _DIF;   } // ?


"fadd"   { return _FADD; }
"fsub"   { return _FSUB; }
"fmul"   { return _FMUL; }
"fdiv"   { return _FDIV; }

"fcos"   { return _FCOS; }
"fsin"   { return _FSIN; }
"ftan"   { return _FTAN; } // ?

"finf"   { return _FINF;   }
"finfeq" { return _FINFEQ; }
"fsup"   { return _FSUP;   }
"fsupeq" { return _FSUPEQ; }
"feq"    { return _FEQ;    } // ?
"fdif"   { return _FDIF;   } // ?


"padd"   { return _PADD;   }
"concat" { return _CONCAT; }


"alloc"  { return _ALLOC;  }
"allocn" { return _ALLOCN; }
"free"   { return _FREE;   }


"equal"  { return _EQUAL; }


"atoi"   { return _ATOI; }
"atof"   { return _ATOF; }
"itof"   { return _ITOF; }
"ftoi"   { return _FTOI; }
"stri"   { return _STRI; }
"strf"   { return _STRF; }


"pushi"  { return _PUSHI;  }
"pushn"  { return _PUSHN;  }
"pushf"  { return _PUSHF;  }
"pushs"  { return _PUSHS;  }
"pushg"  { return _PUSHG;  }
"pushl"  { return _PUSHL;  }
"pushsp" { return _PUSHSP; }
"pushfp" { return _PUSHFP; }
"pushgp" { return _PUSHGP; }
"load"   { return _LOAD;   }
"loadn"  { return _LOADN;  }
"dup"    { return _DUP;    }
"dupn"   { return _DUPN;   }


"pop"    { return _POP;  }
"popn"   { return _POPN; }


"storel" { return _STOREL; }
"storeg" { return _STOREG; }
"store"  { return _STORE;  }
"storen" { return _STOREN; }


"check"  { return _CHECK; }
"swap"   { return _SWAP;  }


"write"  { return _WRITE; }
"read"   { return _READ;   }

"jump"   { return _JUMP;  }
"jz"     { return _JZ;    }
"pusha"  { return _PUSHA; }


"call"   { return _CALL;   }
"return" { return _RETURN; }


"start"  { return _START; }
"nop"    { return _NOP;   }
"err"    { return _ERR;   }
"stop"   { return _STOP;  }


-?[0-9]+"."[0-9]+ { yylval.f = atof(yytext); return _FLOAT; }
-?[0-9]+		      { yylval.i = atoi(yytext); return _INT; }
\"(\\.|[^"\\])*\" { return _STRING; }

[a-z][a-zA-Z0-9]* { return _LABEL; }

[ \t\n]*          { ; }
"//".*            { ; }
.                 { _exit(0);}

%%
