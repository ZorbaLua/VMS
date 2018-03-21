#ifndef TYPES_H
#define TYPES_H

typedef enum etype{
    INTEGER,
    FLOAT,
    STRING,
    POINTER,
    NOTHING
} Etype;

typedef enum inst {
  ADD, SUB, MUL, DIV, MOD, NOT, INF, INFEQ, SUP, SUPEQ, EQ, DIF, FADD, FSUB, FMUL,
  FDIV, FCOS, FSIN, FTAN, FINF, FINFEQ, FSUP, FSUPEQ, FEQ, FDIF, PADD, CONCAT, ALLOC,
  ALLOCN, FREE, EQUAL, ATOI, ATOF, ITOF, FTOI, STRI, STRF, PUSHI, PUSHN, PUSHF, PUSHS,
  PUSHG, PUSHL, PUSHSP, PUSHFP, PUSHGP, LOAD, LOADN, DUP, DUPN, POP, POPN, STOREL, STOREG,
  STORE, STOREN, CHECK, SWAP, WRITEI, WRITEF, WRITES, READ, READI, READF, READS, JUMP,
  JZ, PUSHA, CALL, RETURN, START, NOP, ERR, STOP
} Einst;

typedef union uvalue{
    int i;
    float f;
    char* s;
    int p;
} Uvalue;

typedef struct value{
    Uvalue val;
    Etype type;
} Value;

#endif
