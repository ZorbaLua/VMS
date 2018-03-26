#ifndef TYPES_H
#define TYPES_H

#define MAX_LINE 100

typedef enum etype{
    INT,
    FLOAT,
    CODE_PT,
    OP_PT,
    HEAP_PT,
    NOTHING
} Etype;

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
    EQ,
    DIF,
    FADD,
    FSUB,
    FMUL,
    FDIV,
    FCOS,
    FSIN,
    FTAN,
    FINF,
    FINFEQ,
    FSUP,
    FSUPEQ,
    FEQ,
    FDIF,
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

typedef union uvalue{
    int i;
    float f;
} Uvalue; 

typedef struct value{
    Uvalue val;
    Etype type;
} Value;

Value newValue(Uvalue,Etype);
char* Value_toString(Value);
#endif
