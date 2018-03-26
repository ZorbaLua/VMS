CC=gcc
CFLAGS=-Wall
STRUCTS=structs

main: main.c semantic.o types.o array.o code.o opStack.o callStack.o y.tab.o lex.yy.o #interface.c
	$(CC) $(CFLAGS) main.c types.o array.o code.o opStack.o callStack.o semantic.o lex.yy.o y.tab.o -o main

semantic.o: semantic.c
	$(CC) $(CFLAGS) -c semantic.c

####################################################################################################
#
#interface.c: 
#	$(CC) -o interface interface.c pkg-config --cflags --libs gtk+-3.0
#
####################################################################################################

types.o: $(STRUCTS)/types.c
	$(CC) $(CFLAGS) -c $(STRUCTS)/types.c

array.o: $(STRUCTS)/array.c  
	$(CC) $(CFLAGS) -c $(STRUCTS)/array.c

code.o: $(STRUCTS)/code.c
	$(CC) $(CFLAGS) -c $(STRUCTS)/code.c

opStack.o: $(STRUCTS)/opStack.c
	$(CC) $(CFLAGS) -c $(STRUCTS)/opStack.c

heap.o: $(STRUCTS)/heap.c
	$(CC) $(CFLAGS) -c $(STRUCTS)/heap.c

callStack.o: $(STRUCTS)/callStack.c
	$(CC) $(CFLAGS) -c $(STRUCTS)/callStack.c

####################################################################################################

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
