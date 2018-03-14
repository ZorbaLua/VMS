%{
    /* Declaracoes C diversas */
  #include "linguagem.h"

    /* Variaveis Globais */

  GString *pof=NULL;
  FILE *inFile=NULL;
  FILE *outFile=NULL;

  GHashTable *hDecs = NULL; //atencao as colisoes
  GHashTable *hFunc = NULL; //atencao as colisoes

%}

%token
%type

%%

File : Instructions                     { }

Instructions : Instruction Instructions { }
             |                          { }
             ;

// Mudar nomes
Instruction : Function0                 { }
            | Function1                 { }
            | Function2                 { }
            ; // Incompleto

Function0 : ADD                         { getCalc(&$$, $1); }
          |
          |
          |
          |
          |
          |

|%%

void initArgs(GString **ret) {
  stackA=-1;
  stackL=0;
  *ret = GSN("");
}

void yyerror(const char *s) {
  GString *cmd = GSN("rm -f "); GSAP(cmd, "'%s'", pof->str);
  fprintf(stderr , "\e[1mline:%d: \e[31merror: \e[0m\e[1m%s\e[0m \n" , yylineno, s);
  system(cmd->str);
  printf("cmd=%s\n" , cmd->str);
  _exit(-1);
}

void yywarning(const char *s) {
  fprintf(stderr , "\e[1mline:%d: \e[35warning: \e[0m\e[1m%s\e[0m \n" , yylineno, s);
}

void options(int argc, char **argv, GString *nof, GString *path, GString *pof, GString *pif) {
  int flag = 1;
  char c = -1;

  switch(argc){
    case 1: printf("Missing input file\n"); _exit(-1); break;
    case 3: if ( strncmp(argv[2], "-v",2) == 0 ) flag=0; break;

    case 4:
      c = argv[2][0];
      for(int i = 1; c!='\0'; i++){
        switch(c){
          case 'o': (nof) = GSN(argv[3]); break;
          case 'v': flag=0;               break;
        }
        c = argv[2][i];
      } break;
    }

    GSP ((pif),"%s/%s",(path)->str,argv[1]);
    if ((inFile = fopen((pif)->str,"r")) == NULL ) { fprintf(stderr,"Erro reading input file\n"); _exit(-1); }
    dup2 (fileno(inFile),0);

    GSP((pof),"%s/%s",(path)->str,(nof)->str);
    outFile = fopen((pof)->str, "w");
    if (flag) { int f = open("/dev/null",O_RDONLY);
    dup2(f,1);
  }
}

int main(int argc, char **argv) {
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
