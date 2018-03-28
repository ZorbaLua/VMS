#ifndef TYPES_H
#define TYPES_H

#define MAX_LINE 100

typedef enum etype{
    T_int,
    T_float,
    T_codePt,
    T_opPt,
    T_heapPt,
    NOTHING
} Etype;

typedef int codePt, opPt, heapPt;

typedef union uvalue{
    int i;
    float f;   
    codePt c;
    opPt o;  
    heapPt h;
} Uvalue; 

typedef struct value{
    Uvalue val;
    Etype type;
} Value;


typedef enum inst {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NOT,
    INF,
    INFEQ,
    SUP,
    SUPEQ,
    FADD,
    FSUB,
    FMUL,
    FDIV,
    FINF,
    FINFEQ,
    FSUP,
    FSUPEQ,
    PADD,
    CONCAT,
    ALLOC,
    ALLOCN,
    FREE,
    EQUAL,
    ATOI,
    ATOF,
    ITOF,
    FTOI,
    STRI,
    STRF,
    PUSHI,
    PUSHN,
    PUSHF,
    PUSHS,
    PUSHG,
    PUSHL,
    PUSHSP,
    PUSHFP,
    PUSHGP,
    LOAD,
    LOADN,
    DUP,
    DUPN,
    POP,
    POPN,
    STOREL,
    STOREG,
    STORE,
    STOREN,
    CHECK,
    SWAP,
    WRITE,
    READ,
    JUMP,
    JZ,
    PUSHA,
    CALL,
    RETURN,
    START,
    NOP,
    ERR,
    STOP,
    LABEL
} Einst;



Value newValue(Uvalue,Etype);
char* Value_toString(Value);
char* Inst_toString(Einst);

#endif
