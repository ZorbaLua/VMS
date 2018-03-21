CC=gcc
CFLAGS=-Wall

main: main.c structs/darray.o structs/code.o structs/opStack.o semantic.o parser.o
	$(CC) $(CFLAGS) main.c darray.o code.o opStack.o semantic.o parser.o -o main

semantic.o: semantic.c
	$(CC) $(CFLAGS) -c semantic.c

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

parser.o: lex.l syntax.y
	yacc -d syntax.y
	flex lex.l
	$(CC) $(CFLAGS) -c lex.yy.c y.tab.c 
	$(CC) $(CFLAGS) lex.yy.o y.tab.o -o parser.o 


clean:
	rm -f *.o y.tab.h y.tab.c lex.yy.c
