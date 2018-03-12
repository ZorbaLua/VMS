#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

#include <glib.h>

#define MAX_PATH 1000
/* variaveis globais */
extern int stackG;
extern int stackL;
extern int stackA;
extern char gl;
extern char typeExp;

extern int ifLabel;
extern int whileLabel;
extern int forLabel;

extern GString *pof;
extern FILE *inFile;
extern FILE *outFile;

GHashTable *hDecs;
GHashTable *hFunc;

extern int yylineno;


enum{ INTEIRO, GSTRING };

/* glib function rename *******************************/

#define GSN(a) g_string_new(a)
#define GSAP(...) g_string_append_printf (__VA_ARGS__)
#define GSP(...) g_string_printf(__VA_ARGS__)
#define GSPP(...) g_string_prepend(__VA_ARGS__)
#define SFREE(...) g_string_free(__VA_ARGS__,TRUE)


#define insertDecs(...) g_hash_table_insert(hDecs,__VA_ARGS__)
#define lookupDecs(...) g_hash_table_lookup(hDecs,__VA_ARGS__)
#define removeDecs(...) g_hash_table_remove(hDecs,__VA_ARGS__)

#define insertFunc(...) g_hash_table_insert(hFunc,__VA_ARGS__)
#define lookupFunc(...) g_hash_table_lookup(hFunc,__VA_ARGS__)
#define removeFunc(...) g_hash_table_remove(hFunc,__VA_ARGS__)

/******************************************************/

void yyerror(const char *s);

void yywarning(const char *s);

int yylex();

void initArgs(GString **ret);

/* attribution.c **************************************/

int getWrite(GString **ret, char type, GString *expWrite);

int getRead(GString **ret, char type);

int getDeclareArg(GString **ret, char type, GString *name);

int getCallFunction(GString **ret, GString *name, GString *args);

int getArgsList(GString **ret, GString *args, char type, GString *name);

int getDeclareFunction(GString **ret, char typeRet, GString *name, GString *args, GString *decl, GString *procedures, GString *retExp);

int getFunctionCall(GString **ret, GString *name);

int getDeclareVar(GString **ret, char type, GString *name, GSList *dim, GString *expVal);

int getITE(GString **ret, GString *cond, GString *trueBlock, GString *falseBlock);

int getFalse(GString **ret, GString *blockFalse);
int getTrue(GString **ret, GString *blockTrue);
int getExpR(GString **ret, GString *firstExp, char rel, GString *secondExp);

int getExpL(GString **ret, GString *listaC, char operadorLogico, GString *ExpR);

int getVar(GString **ret, GString *name, GSList *index);
int getAtr(GString **ret, GString *name, GSList *index, GString *exp);
int storeVar(GString **ret, GString *name, GSList *index);


int getBlockDeclarations(GString **ret, GString *Declarations, GString *Declaration);

int getBlockProcedures(GString **ret, GString *Procedures, GString *Procedure);

int getCalc(GString **ret, GString *firstExp, char operador, GString *secondExp);

int getWhile(GString **ret, GString *cond, GString *Procedures);

int getFor(GString **ret, GString *atr, GString *cond, GString *inc, GString* procedures);


/* struct.c *******************************************/

int calcLen(GSList *dim);

typedef struct hashData{
    char type;
    int pt;
    int len;
    GSList *dim;
    char gl;
} *HashData;

typedef struct hashFunc{
    char type;
    GString *args;
} *HashFunc;

typedef struct tuple{
    GString *first;
    GString *second;
} *Tuple;

void hdPrint(HashData hd);

void hfPrint(HashFunc hf);

HashData newHashData(char type, GSList *dim, char varArg);

HashFunc newHashFunc(char type, GString *args);

int converToIndex(GString *name, GSList *indexL);

int converToIndexExp(GString **ret, GString *name, GSList *indexL);

int isArray(char type);

Tuple newTuple(GString *first, GString *second);

void monadExp(char type);
