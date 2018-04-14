CC=gcc -g
CFLAGS=-Wall
STRUCTS=structs
GTK_LIBS=`pkg-config --cflags --libs gtk+-3.0`
GLIBS=`pkg-config --cflags --libs glib-2.0` 
CFLAGS_GLIB=`pkg-config --cflags glib-2.0` 


all: main interface

main: main.c semantic.o types.o array.o linkedlist.o code.o opStack.o callStack.o heap.o y.tab.o lex.yy.o 
	$(CC) $(CFLAGS) $(GLIBS) main.c semantic.o types.o array.o linkedlist.o code.o opStack.o callStack.o heap.o y.tab.o lex.yy.o -o main

interface: interface.c 
	$(CC) $(GTK_LIBS) interface.c -o interface 

####################################################################################################

semantic.o: semantic.c
	$(CC) $(CFLAGS) $(CFLAGS_GLIB)-c semantic.c

####################################################################################################

array.o: $(STRUCTS)/array.c  
	$(CC) $(CFLAGS) -c $(STRUCTS)/array.c

linkedlist.o: $(STRUCTS)/linkedlist.c
	$(CC) $(CFLAGS) -c $(STRUCTS)/linkedlist.c

####################################################################################################

types.o: $(STRUCTS)/types.c
	$(CC) $(CFLAGS) $(CFLAGS_GLIB) -c $(STRUCTS)/types.c

code.o: $(STRUCTS)/code.c
	$(CC) $(CFLAGS) $(CFLAGS_GLIB) -c $(STRUCTS)/code.c

opStack.o: $(STRUCTS)/opStack.c
	$(CC) $(CFLAGS) $(CFLAGS_GLIB) -c $(STRUCTS)/opStack.c

heap.o: $(STRUCTS)/heap.c
	$(CC) $(CFLAGS) $(CFLAGS_GLIB) -c $(STRUCTS)/heap.c

callStack.o: $(STRUCTS)/callStack.c
	$(CC) $(CFLAGS) $(CFLAGS_GLIB) -c $(STRUCTS)/callStack.c

####################################################################################################

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) $(CFLAGS_GLIB) -c y.tab.c

y.tab.c: syntax.y
	yacc -d syntax.y

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) $(CFLAGS_GLIB) -c lex.yy.c

lex.yy.c: lex.l
	flex -l lex.l

####################################################################################################
clean:
	rm -f *.o y.tab.h y.tab.c lex.yy.c main interface
