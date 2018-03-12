%{
#include "linguagem.h"
/* Declaracoes C diversas */
/* variaveis globais */

int stackG=0;
int stackL=0;
int stackA=-1;
char gl='g';
char typeExp='e';

int ifLabel=0;
int whileLabel=0;
int forLabel=0;

GString *pof=NULL;
FILE *inFile=NULL;
FILE *outFile=NULL;

GHashTable *hDecs = NULL; //atencao as colisoes
GHashTable *hFunc = NULL; //atencao as colisoes



%}

%union{
    GString *string;
    GSList *list;
    char cha;
    int integer;
    float fl;
    Tuple twoString;
}


%token  IF ELSE WHILE FOR IN RET DEF CALL

%type   <list> Index Dim

%token  <integer> INT  
%token  <fl> FLOAT

%token 	<string> ID BOOL STRING
%type   <string> File Function Functions Procedure Procedures Declaration Declarations Decl BlockIns
%type   <string> Ite For While Write Else
%type   <string> CallArgs ListArgs InvListExp ArgWrite ListExp ListAtr
%type   <string> Num Exp Par Term ExpR ExpL TermL Args Atr 

%token 	<cha> VOID TINT TFLOAT REL WRITE READ OCP OSP OL 
%type   <cha> Type  

%%

File        : Declarations Functions Procedures                         { fprintf(outFile, "%sstart\n%sstop\n%s", $1->str, $3->str, $2->str); }

Functions   : Functions Function                                        { GSAP($$, "%s%s",$1->str, $2->str); }
            |                                                           { gl = 'l'; $$ = GSN(""); }
            ;

Function    : DEF Type ID Args'{'Declarations Procedures RET ExpL';''}' { getDeclareFunction(&$$, $2, $3, $4, $6, $7, $9); }
            | DEF VOID ID Args'{'Declarations Procedures'}'             { getDeclareFunction(&$$, $2, $3, $4, $6, $7,NULL); }
            ;

            
Args        : '('ListArgs')'                                            { $$ = $2; }
            | '('')'                                                    { $$ = GSN(""); }
            ;

ListArgs    : ListArgs ',' Type ID                                      { getArgsList(&$$, $1, $3, $4); }
            | Type ID                                                   { initArgs(&$$); getDeclareArg(&$$, $1, $2); }
            ;


Declarations: Declarations Declaration                                  { getBlockDeclarations(&$$, $1, $2); }
            |                                                           { $$ = GSN(""); }
            ;


Declaration : Type ID Dim Decl                                          { getDeclareVar(&$$, $1, $2, $3, $4); }
            ;


Decl        : '=' '{'ListExp'}'                                         { $$ = $3; }
            | '=' Exp ';'                                               { $$ = $2; }
            | ';'                                                       { $$ = GSN(""); }
            ;


Type        : TINT                                                      { $$ = $1; } 
            | TFLOAT                                                    { $$ = $1; }
            ;


Num         : INT                                                       { monadExp('i'); $$ = GSN("pushi "); GSAP($$, "%d\n", $1); }
            | FLOAT                                                     { monadExp('f'); $$ = GSN("pushf "); GSAP($$, "%f\n", $1); }
            ;


BlockIns    : '{'Procedures'}'                                          { $$ = $2; }
            | Procedure                                                 { $$ = $1; }
            ;



Procedures  : Procedures Procedure                                      { getBlockProcedures(&$$, $1, $2); typeExp='e'; }  
            |                                                           { $$ = GSN(""); }
            ;


Procedure   : Write ';'                                                 { $$ = $1; }
            | Atr ';'                                                   { $$ = $1; }
            | While                                                     { $$ = $1; }
            | For                                                       { $$ = $1; }
            | Ite                                                       { $$ = $1; }
            ;

Atr         : ID Index '=' Exp                                          { getAtr(&$$, $1, $2, $4); }                            
Write       : WRITE'('ArgWrite')'                                       { getWrite(&$$, $1, $3); }
While       : WHILE '('ExpL')' BlockIns                                 { getWhile(&$$, $3, $5); }
For         : FOR'('ListAtr';' ExpL';' ListAtr')'BlockIns               { getFor(&$$, $3, $5, $7, $9); }
Ite         : IF '('ExpL')' BlockIns Else                               { getITE(&$$, $3, $5, $6); }

Else        : ELSE BlockIns                                             { $$ = $2; }
            |                                                           { $$ = GSN(""); }
            ;

ArgWrite    : Exp                                                       { $$ = $1; }
            | STRING                                                    { $$ = $1; }
            ;

ExpL        : ExpL OL TermL                                             { getExpL(&$$, $1, $2, $3);}
            | TermL                                                     { $$ = $1; }
            ;
            
TermL       : '(' ExpL ')'                                              { $$ = $2; }
            | ExpR                                                      { $$ = $1; }
            ;

ExpR        : Exp REL Exp                                               { getExpR(&$$, $1, $2, $3); typeExp='e'; }

Exp         : Exp OSP Par                                               { getCalc(&$$, $1, $2, $3); }
            | Par                                                       { $$ = $1; }
            ;

Par         : Par OCP Term                                              { getCalc(&$$, $1, $2, $3); }
            | Term                                                      { $$ = $1; }
            ;

Term        : Num                                                       { $$ = $1; }
            | '(' Exp ')'                                               { $$ = $2; }
            | BOOL                                                      { $$ = $1; }
            | ID Index                                                  { getVar(&$$, $1, $2);       /*lookahead = "[" */}
            | CALL ID CallArgs                                          { getCallFunction(&$$, $2, $3); /*lookahead = "(" */}
            | READ '('')'                                               { getRead(&$$, $1); }
            ;




Dim         : Dim '['INT']'                                             { $$ = g_slist_append($$, GINT_TO_POINTER($3)); }
            |                                                           { GSList* list = NULL; $$ = list; }
            ;

Index       : Index '['Exp']'                                           { $$ = g_slist_append($$, $3); }
            |                                                           { GSList* list = NULL; $$ = list; }
            ;

CallArgs    : '('InvListExp')'                                          { $$ = $2; }
            | '('')'                                                    { $$ = GSN(""); }
            ;

InvListExp  : InvListExp','Exp                                          { GSPP($1, $3->str); $$ = $1; }
            | Exp                                                       { $$ = $1; }
            ;

ListExp     : ListExp','Exp                                             { GSAP($1, "%s", $3->str); $$ = $1; }
            | Exp                                                       { $$ = $1; }
            ;

ListAtr     : ListAtr','Atr                                             { GSAP($1, "%s", $3->str); $$ = $1; }
            | Atr                                                       { $$ = $1; }
            ;

%%

void initArgs(GString **ret){
    stackA=-1;
    stackL=0;  
    *ret = GSN("");
}

void yyerror(const char *s){
    GString *cmd = GSN("rm -f "); GSAP(cmd, "'%s'", pof->str); 

    fprintf(stderr , "\e[1mline:%d: \e[31merror: \e[0m\e[1m%s\e[0m \n" , yylineno, s);
    system(cmd->str);
printf("cmd=%s\n" , cmd->str);
    _exit(-1);
}

void yywarning(const char *s){
    fprintf(stderr , "\e[1mline:%d: \e[35warning: \e[0m\e[1m%s\e[0m \n" , yylineno, s);
}




void options(int argc, char **argv, GString *nof, GString *path, GString *pof, GString *pif){
    int flag = 1;
    char c = -1;

    switch(argc){
        case 1:
            printf("Missing input file\n");
            _exit(-1);
        break;

        case 3:
            if( strncmp(argv[2], "-v",2)==0 ) flag=0;
        break;

        case 4:
            c = argv[2][0];
            for(int i = 1; c!='\0'; i++){
                switch(c){
                    case 'o': (nof) = GSN(argv[3]);    break;
                    case 'v': flag=0;                   break;
                }
                c = argv[2][i];
            }
        break;
    } 
    GSP((pif),"%s/%s",(path)->str,argv[1]);
    if( (inFile = fopen((pif)->str,"r")) == NULL ) { fprintf(stderr,"Erro reading input file\n"); _exit(-1); }
    dup2(fileno(inFile),0);

    GSP((pof),"%s/%s",(path)->str,(nof)->str);
    outFile = fopen((pof)->str, "w");
    if(flag){
        int f = open("/dev/null",O_RDONLY);
        dup2(f,1);
    }
}



int main(int argc, char **argv){
    GString *nof = GSN("a.vm");
    GString *path = g_string_new_len("",MAX_PATH); getcwd(path->str, MAX_PATH);
    GString *pif = GSN("");
    pof = GSN("");
    hDecs = g_hash_table_new(g_str_hash, g_str_equal); //atencao as colisoes
    hFunc = g_hash_table_new(g_str_hash, g_str_equal);

    options(argc, argv, nof, path, pof, pif);

    printf("output file path: %s\n",pof->str);
    printf("input file path: %s\n",pif->str);

    printf("beginning parsing\n"); 
	yyparse();
    printf("parsing finished\n");

    fclose(outFile);
    fclose(inFile);

	exit(0);
}

