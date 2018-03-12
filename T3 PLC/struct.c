#include "linguagem.h"



int converToIndex(GString *name, GSList *indexL){
    HashData hd = lookupDecs(name->str);
    int ret = 0;
    
    int i=0;
    for (GSList *itIndex = indexL; itIndex; itIndex = itIndex->next){
        int par = (int)itIndex->data; 
        int j=0;
        for(GSList *itDim = hd->dim; itDim && j<i; itDim = itDim->next){
            par *= (int)itDim->data;
            j++;
        }
        i++;
        ret += par;
    }
    return ret;
}

int converToIndexExp(GString **ret, GString *name, GSList *indexL){
    HashData hd = lookupDecs(name->str);
    *ret = GSN("pushi 0\n");
    //if(hd->len == 0){ GSAP(*ret, "pushi 0\n"); return 0;}

    int i=0; 
    for (GSList *itIndex = indexL; itIndex; itIndex = itIndex->next){
        GString *par = GSN(""); GSAP(par,"%s",((GString*)itIndex->data)->str);
//printf("componente index:%s\n", ((GString*)itIndex->data)->str);
        int j=0;
        for(GSList *itDim = hd->dim; itDim && j<i; itDim = itDim->next){
            GSAP(par, "pushi %d\n",(int)itDim->data);
            GSAP(par, "mul\n");
            j++;
        }
        i++;
        GSAP(*ret, "%s",par->str);
        GSAP(*ret, "add\n"); 
    }

    return 0;
}

int calcLen(GSList *dim){
    int len = 1;
    if(dim == NULL) return 0;
    for(GSList *it = dim; it; it=it->next) len *= (int)it->data;

    return len;
}

HashData newHashData(char type, GSList *dim, char varArg){
    int len = calcLen(dim);
    HashData hd = (HashData)malloc(sizeof(struct hashData));

    if(gl == 'g'){
        hd->pt = stackG;
        if(len)stackG += len;
        else stackG++;
        hd->gl = 'g';
    }
    else if(varArg == 'a'){
        hd->pt = stackA;
        if(len)stackA -= len;
        else stackA--;
        hd->gl = 'l';
    }
    else{
        hd->pt = stackL;
        if(len)stackL += len;
        else stackL++;
        hd->gl = 'l';
    }
    hd->type = type;
    hd->len  = len;
    hd->dim  = dim;
    return hd;
}

void hdPrint(HashData hd){
    printf("\n");
    printf("estrutura a inserir na hash\n");
    printf("\ttype: %c\n",hd->type);
    printf("\tpointer: %d\n",hd->pt);
    printf("\tlength: %d\n",hd->len);
    printf("\tglobal/local: %c\n",hd->gl);
}


HashFunc newHashFunc(char type, GString *args){
    HashFunc hf = (HashFunc)malloc(sizeof(struct hashFunc));
    hf->type = type;
    hf->args = args;
    return hf;
}
void hfPrint(HashFunc hf){
    printf("dados de funcao\n");
    printf("\treturn type: %c\n",hf->type);
    printf("\targuments type: %s\n",hf->args->str);
    printf("\tnumber of args:%lu\n", hf->args->len);
}

Tuple newTuple(GString *first, GString *second){
    Tuple tup = (Tuple)malloc(sizeof(struct tuple));
    tup->first = first;
    tup->second = second;

    return tup;
}

int isArray(char type){
    if(type == 'i' || type == 'f') return 0;
    return 1;
}

void monadExp(char type){
    if(typeExp == 'e') typeExp = type;
    else if( typeExp != type) yyerror("operation with different types");
}
