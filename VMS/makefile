CC=gcc
CFLAGS=-Wall

main: main.c semantic.o parser structs
	$(CC) $(CFLAGS) main.c types.o darray.o code.o opStack.o semantic.o lex.yy.o y.tab.o -o main

semantic.o: semantic.c
	$(CC) $(CFLAGS) -c semantic.c

####################################################################################################
structs: structs/types.o structs/darray.o structs/code.o structs/opStack.o

structs/types.o: structs/types.c
	$(CC) $(CFLAGS) -c structs/types.c

structs/darray.o: structs/darray.c
	$(CC) $(CFLAGS) -c structs/darray.c

structs/code.o: structs/code.c
	$(CC) $(CFLAGS) -c structs/code.c

structs/opStack.o: structs/opStack.c
	$(CC) $(CFLAGS) -c structs/opStack.c

structs/heap.o: structs/heap.c
	$(CC) $(CFLAGS) -c structs/heap.c

structs/callStack.o: structs/callStack.c
	$(CC) $(CFLAGS) -c structs/callStack.c

####################################################################################################
parser: y.tab.o lex.yy.o

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c y.tab.c

y.tab.c: syntax.y
	yacc -d syntax.y

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: lex.l
	flex -l lex.l

####################################################################################################
clean:
	rm -f *.o y.tab.h y.tab.c lex.yy.c
