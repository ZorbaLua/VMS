#include "linguagem.h"



int getDeclareArg(GString **ret, char type, GString *name){
    HashData hd = newHashData(type, NULL, 'a');
hdPrint(hd);
    insertDecs(name->str, hd);
    *ret = GSN("");

    if(type =='v') yyerror("function argument declared as void"); 
    if(type < 'A') yyerror("function argument declared as array"); 
    
    GSAP(*ret, "%c",type);
printf("variable \e[1m%s\e[0m declared with success \n", name->str);

    return 0;
}


int getArgsList(GString **ret, GString *args, char type, GString *name){
    GString *aux; 
    getDeclareArg(&aux, type, name); 
    *ret = GSN("");
    GSAP(*ret, "%s%s", args->str, aux->str);

    return 0;
}


int getDeclareFunction(GString **ret, char typeRet, GString *name, GString *args, GString *decl,  GString *procedures, GString *retExp){
    HashFunc hf = newHashFunc(typeRet, args);
    insertFunc(name->str, hf);

    *ret = GSN("\t// declaracao funcao\n");

    GSAP(*ret, "%s: nop         \n", name->str          );
    GSAP(*ret, "%s              \n", procedures->str    );
    GSAP(*ret, "%s              \n", decl->str          );
    if(retExp!=NULL){
        GSAP(*ret, "%s          \n", retExp->str        );
        GSAP(*ret, "storel -%lu \n", (hf->args->len)+1  );
        SFREE(retExp);
    }
    GSAP(*ret, "return          \n"                     );
    hf = NULL;
    hf = lookupFunc(name->str);

//    SFREE(procedures);
    return 0;
}


int getCallFunction(GString **ret, GString *name, GString *argumentos){
    HashFunc hf = lookupFunc(name->str);
    if(!hf) yyerror("function not declared");
printf("funcao-> %s\n", name->str);
hfPrint(hf);
    *ret = GSN("");

    GSAP(*ret, "\t// preparar funcao\n"                   );
    GSAP(*ret, "push%c 0 // return  \n", hf->type         );
    GSAP(*ret, "\t// args da fucao  \n"                   );
    GSAP(*ret, "%s                  \n", argumentos->str  );
    GSAP(*ret, "\t// chamar a funcao\n"                   );
    GSAP(*ret, "pusha %s            \n", name->str        );
    GSAP(*ret, "call                \n"                   );
    GSAP(*ret, "nop                 \n"                   );
    GSAP(*ret, "\t//retira da stack os argumentos\n"      );
    GSAP(*ret, "pop %lu             \n", (hf->args)->len  );

//    SFREE(argumentos);
    return 0;
}

int getDeclareVar(GString **ret, char type, GString *name, GSList *dim, GString *expVal){
    if(dim) type+= 'A'-'a'; 
    HashData hd = newHashData(type, dim, 'v');
    *ret = GSN("\t// inicio declaracao da variavel "); 

hdPrint(hd);    
    GSAP(*ret, "\"%s\"\n", name->str);
    GSAP(*ret, "%s", expVal->str);
    char p[11]="";

    insertDecs(name->str, hd);
    if(expVal->len == 0){
        switch(type){ 
            case 'i': GSAP(*ret, "pushi 0\n");          break;
            case 'f': GSAP(*ret, "pushf 0.0\n");        break;
            case 'I': strncpy(p, "pushi 0\n\0", 11);    break;
            case 'F': strncpy(p, "pushf 0.0\n\0", 11);  break;
        }
        if( isArray(type) ) for(int i=0, len=calcLen(dim); i<len; i++) GSAP(*ret, "%s", p);
    }
    GSAP(*ret, "\t// fim declaracao da variavel \"%s\"\n", name->str);
printf("variable \e[1m%s\e[0m declared with success \n", name->str);
    
    return 0;
}


int getITE(GString **ret, GString *cond, GString *trueBlock, GString *falseBlock){
    GString *expTrue; getTrue(&expTrue, trueBlock);
    GString *expFalse; getFalse(&expFalse, falseBlock);

    *ret = GSN("\t// incicio de ite     \n");
    GSAP(*ret, "%s", cond->str             );
    GSAP(*ret, "\t// comeca bloco THEN  \n");
    GSAP(*ret, "%s", expTrue->str          );
    GSAP(*ret, "\t// comeca bloco ELSE  \n");
    GSAP(*ret, "%s", expFalse->str         );
    GSAP(*ret, "\t// fim de ite         \n");
    ifLabel++;

//    SFREE(cond);
    return 0;
}

int getFalse(GString **ret, GString *blockFalse){
    *ret = GSN("ELSE");

    GSAP(*ret, "%d:\n%sENDIF%d:\n", ifLabel, blockFalse->str, ifLabel);

    SFREE(blockFalse);
    return 0;
}

int getTrue(GString **ret, GString *blockTrue){
    *ret = GSN("jz ELSE");

    GSAP(*ret, "%d\n%sjump ENDIF%d\n", ifLabel, blockTrue->str,ifLabel);

//    SFREE(blockTrue);
    return 0;
}
int getExpR(GString **ret, GString *firstExp, char rel, GString *secondExp){
    GString *fExp = GSN("");
    GString *relExp;
    *ret = GSN("");

    if(typeExp == 'f') GSAP(fExp, "f");
    switch(rel){
        case('l'): relExp = GSN("inf\n");         break;
        case('g'): relExp = GSN("sup\n");         break;
        case('L'): relExp = GSN("infeq\n");       break;
        case('G'): relExp = GSN("supeq\n");       break;
        case('e'): relExp = GSN("equal\n");       break;
        case('n'): relExp = GSN("equal\nnot\n");  break;
    }
    GSAP(*ret, "%s%s%s%s", firstExp->str, secondExp->str, fExp->str, relExp->str);
printf("ExpRel:\n%s\n",(*ret)->str);

//    SFREE(firstExp);
//    SFREE(relExp);
//    SFREE(secondExp);
    return 0;
}

int getExpL(GString **ret, GString *firstExp, char operadorLogico, GString *secondExp){
    GString *olExp;
    *ret = GSN("");

    switch(operadorLogico){
        case('a'): 
            olExp = GSN("add\n");
            GSAP(olExp, "pushi 2\n");
            GSAP(olExp, "equal\n");
        break;
        case('o'):
            olExp = GSN("add\n");
            GSAP(olExp, "pushi 0\n");
            GSAP(olExp, "sup\n");
        break;
    }
    GSAP(*ret, "%s%s%s", firstExp->str, secondExp->str, olExp->str);
    
//    SFREE(firstExp);
//    SFREE(olExp);
//    SFREE(secondExp);
    return 0;
}


int getAtr(GString **ret, GString *name, GSList *index, GString *exp){
    HashData hd = lookupDecs(name->str); 
    GString *ind = GSN(""); 
    *ret = GSN("");
if( !hd ) yyerror("var not declared");
    if( !isArray(hd->type) ){
        GSAP(*ret, "%s"          , exp->str      );
        GSAP(*ret, "store%c %d\n", hd->gl, hd->pt);
    }
    else{
        converToIndexExp(&ind, name, index);

        if(hd->gl == 'g')   GSAP(*ret, "pushgp\n");
        else                GSAP(*ret, "pushfp\n");
        GSAP(*ret, "pushi %d    \n", hd->pt      );
        GSAP(*ret, "%s"            , ind->str    );
        GSAP(*ret, "add         \n"              );
        GSAP(*ret, "%s"          , exp->str      );
        GSAP(*ret, "storen      \n"              );
    }


    return 0;
}

/*
int storeVar(GString **ret, GString *name, GSList *index){
    return 0;
}
*/

int getVar(GString **ret, GString *name, GSList *index){
    HashData hd = lookupDecs(name->str); 
    GString *ind = GSN(""); 
    *ret = GSN("\t// inicio de get variavel "); GSAP(*ret, "\"%s\"\n", name->str);
if( !hd ) yyerror("var not declared");
    if( !isArray(hd->type) ){
        GSAP(*ret, "push%c %d", hd->gl, hd->pt);
    }
    else{
        converToIndexExp(&ind, name, index);

        if(hd->gl == 'g')   GSAP(*ret, "pushgp\n");
        else                GSAP(*ret, "pushfp\n");
        GSAP(*ret, "pushi %d    \n", hd->pt   );
        GSAP(*ret, "%s"            , ind->str );
        GSAP(*ret, "add         \n"           );
        GSAP(*ret, "loadn       \n"           );
    }
    GSAP(*ret, "\t// fim de get variavel \"%s\"\n", name->str);

    return 0; 
}

int getBlockDeclarations(GString **ret, GString *declarations, GString *declaration){
    *ret = GSN("");
    GSAP(*ret, "%s%s", declarations->str, declaration->str);

//    SFREE(declarations);
//    SFREE(declaration);
    return 0;
}

int getBlockProcedures(GString **ret, GString *procedures, GString *procedure){
    *ret = GSN("");
    GSAP(*ret, "%s%s", procedures->str, procedure->str);

//    SFREE(procedures);
//    SFREE(procedure);
    return 0;
}

int getCalc(GString **ret, GString *firstExp, char operador, GString *secondExp){
    GString *fExp = GSN("");
    GString *oExp;
    *ret = GSN("");

    if(typeExp == 'f') GSAP(fExp, "f");
    switch(operador){
        case'+': oExp = GSN("add\n"); break;
        case'-': oExp = GSN("sub\n"); break;
        case'*': oExp = GSN("mul\n"); break; 
        case'/': oExp = GSN("div\n"); break;
        case'%': oExp = GSN("mod\n"); if(typeExp!='i') yyerror("operation mod not permited"); break;
    }
    GSAP(*ret, "%s%s%s%s", firstExp->str, secondExp->str, fExp->str, oExp->str);

//    SFREE(firstExp);
//    SFREE(oExp);
//    SFREE(secondExp);
    return 0;
}


int getWhile(GString **ret, GString *cond, GString *procedures){
    *ret = GSN("\n\t// inicio do ciclo while\n");
    GSAP(*ret, "WHILE%d:             \n", whileLabel        );
    GSAP(*ret, "\t//condicao de permanencia no ciclo   \n"  );
    GSAP(*ret, "%s"                     , cond->str         );
    GSAP(*ret, "jz ENDWHILE%d        \n", whileLabel        );
    GSAP(*ret, "%s"                     , procedures->str   );
    GSAP(*ret, "jump WHILE%d         \n", whileLabel        );
    GSAP(*ret, "ENDWHILE%d:          \n", whileLabel        );
    GSAP(*ret, "\t// fim do ciclo while\n\n"                );

    whileLabel++;

//    SFREE(cond);
//    SFREE(procedures);
    return 0;
}


int getFor(GString **ret, GString *atr, GString *cond, GString *inc, GString* procedures){
    *ret = GSN("");

    GSAP(*ret, "\t// atribuicoes iniciais for\n"            );
    GSAP(*ret, "%s"                     , atr->str          ); 
    GSAP(*ret, "FOR%d:               \n", forLabel          );
    GSAP(*ret, "\t// cond de permanencia\n"                 );
    GSAP(*ret, "%s"                     , cond->str         );
    GSAP(*ret, "jz ENDFOR%d          \n", forLabel          );
    GSAP(*ret, "\t// inicio de bloco do ciclo\n"            );
    GSAP(*ret, "%s"                     , procedures->str   ); 
    GSAP(*ret, "\t// incremento das variaveis\n"            );
    GSAP(*ret, "%s"                     , inc->str          ); 
    GSAP(*ret, "jump FOR%d:          \n", forLabel          ); 
    GSAP(*ret, "ENDFOR%d:            \n", forLabel          );

    forLabel++;
    return 0;
}


int getWrite(GString **ret, char type, GString *expWrite){
    *ret = GSN("");

    if(type == 's'){
        GSAP(*ret, "pushs %s            \n", expWrite->str);
        GSAP(*ret, "write%c             \n", type       );
        
    }
    else{
        GSAP(*ret, "%s                  \n", expWrite->str);
        GSAP(*ret, "write%c             \n", type       );
    }

    return 0;
}

int getRead(GString **ret, char type){
    *ret = GSN("");

    GSAP(*ret, "read            \n"                 );
    GSAP(*ret, "ato%c           \n", type           );

    return 0;
}
