

int iCode    = 0;
int iHeap    = 0;
int iCall    = 0;
int iOPStack = 0;

enum functions {
  ADD, SUB, MUL, DIV, MOD, NOT, INF, INFEQ, SUP, SUPEQ, EQ, DIF, FADD, FSUB, FMUL,
  FDIV, FCOS, FSIN, FTAN, FINF, FINFEQ, FSUP, FSUPEQ, FEQ, FDIF, PADD, CONCAT, ALLOC,
  ALLOCN, FREE, EQUAL, ATOI, ATOF, ITOF, FTOI, STRI, STRF, PUSHI, PUSHN, PUSHF, PUSHS,
  PUSHG, PUSHL, PUSHSP, PUSHFP, PUSHGP, LOAD, LOADN, DUP, DUPN, POP, POPN, STOREL, STOREG,
  STORE, STOREN, CHECK, SWAP, WRITEI, WRITEF, WRITES, READ, READI, READF, READS, JUMP,
  JZ, PUSHA, CALL, RETURN, START, NOP, ERR, STOP  break; };

  //-----------------------------------------//

switch(func){
  case ADD:    { break; }
  case SUB:    { break; }
  case MUL:    { break; }
  case DIV:    { break; }
  case MOD:    { break; }
  case NOT:    { break; }
  case INF:    { break; }
  case INFEQ:  { break; }
  case SUP:    { break; }
  case SUPEQ:  { break; }
  case EQ:     { break; }
  case DIF:    { break; }
  case FADD:   { break; }
  case FSUB:   { break; }
  case FMUL:   { break; }
  case FDIV:   { break; }
  case FCOS:   { break; }
  case FSIN:   { break; }
  case FTAN:   { break; }
  case FINF:   { break; }
  case FINFEQ: { break; }
  case FSUP:   { break; }
  case FSUPEQ: { break; }
  case FEQ:    { break; }
  case FDIF:   { break; }
  case PADD:   { break; }
  case CONCAT: { break; }
  case ALLOC:  { break; }
  case ALLOCN: { break; }
  case FREE:   { break; }
  case EQUAL:  { break; }
  case ATOI:   { break; }
  case ATOF:   { break; }
  case ITOF:   { break; }
  case FTOI:   { break; }
  case STRI:   { break; }
  case STRF:   { break; }
  case PUSHI:  { break; }
  case PUSHN:  { break; }
  case PUSHF:  { break; }
  case PUSHS:  { break; }
  case PUSHG:  { break; }
  case PUSHL:  { break; }
  case PUSHSP: { break; }
  case PUSHFP: { break; }
  case PUSHGP: { break; }
  case LOAD:   { break; }
  case LOADN:  { break; }
  case DUP:    { break; }
  case DUPN:   { break; }
  case POP:    { break; }
  case POPN:   { break; }
  case STOREL: { break; }
  case STOREG: { break; }
  case STORE:  { break; }
  case STOREN: { break; }
  case CHECK:  { break; }
  case SWAP:   { break; }
  case WRITEI: { break; }
  case WRITEF: { break; }
  case WRITES: { break; }
  case READ:   { break; }
  case READI:  { break; }
  case READF:  { break; }
  case READS:  { break; }
  case JUMP:   { break; }
  case JZ:     { break; }
  case PUSHA:  { break; }
  case CALL:   { break; }
  case RETURN: { break; }
  case START:  { break; }
  case NOP:    { break; }
  case ERR:    { break; }
  case STOP:   { break; }
  default:     { printf("Faltou adicionar o novo comando"); break; }
