CC=gcc -g
CFLAGS=-Wall
STRUCTS=structs
GTK_LIBS=`pkg-config --cflags --libs gtk+-3.0`
GLIBS=`pkg-config --cflags --libs glib-2.0`
GTK_FLAGS=`pkg-config --cflags gtk+-3.0`
GLIB_FLAGS=`pkg-config --cflags glib-2.0`


interface: main.c semantic.o types.o array.o code.o opStack.o callStack.o heap.o y.tab.o lex.yy.o interface.o
	$(CC) $(CFLAGS) $(GTK_LIBS) $(GLIBS) main.c semantic.o types.o array.o code.o opStack.o callStack.o heap.o y.tab.o lex.yy.o interface.o -o interface

semantic.o: semantic.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c semantic.c

####################################################################################################

interface.o: interface.c
	$(CC) $(CFLAGS) $(GTK_FLAGS) -c interface.c 
####################################################################################################

array.o: $(STRUCTS)/array.c
	$(CC) $(CFLAGS) -c $(STRUCTS)/array.c

####################################################################################################

types.o: $(STRUCTS)/types.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c $(STRUCTS)/types.c

code.o: $(STRUCTS)/code.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c $(STRUCTS)/code.c

opStack.o: $(STRUCTS)/opStack.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c $(STRUCTS)/opStack.c

heap.o: $(STRUCTS)/heap.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c $(STRUCTS)/heap.c

callStack.o: $(STRUCTS)/callStack.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c $(STRUCTS)/callStack.c

####################################################################################################

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c y.tab.c

y.tab.c: syntax.y
	yacc -d syntax.y

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c lex.yy.c

lex.yy.c: lex.l
	flex -l lex.l

####################################################################################################
clean:
	rm -f *.o y.tab.h y.tab.c lex.yy.c main
