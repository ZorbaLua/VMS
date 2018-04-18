CC=cc -g
CFLAGS=-Wall
STRUCTS=structs
GTK_LIBS=`pkg-config --cflags --libs gtk+-3.0`
GTK_FLAGS=`pkg-config --cflags gtk+-3.0`
GLIB_LIBS=`pkg-config --cflags --libs glib-2.0`
GLIB_FLAGS=`pkg-config --cflags glib-2.0`


all: main interface

main: main.c semantic.o types.o array.o code.o opStack.o callStack.o heap.o y.tab.o lex.yy.o
	$(CC) $(CFLAGS) main.c semantic.o types.o array.o code.o opStack.o callStack.o heap.o y.tab.o lex.yy.o $(GTK_LIBS) -o main

interface: interface.c
	$(CC) interface.c $(GTK_LIBS) -o interface

####################################################################################################

semantic.o: semantic.c
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -c semantic.c

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
	flex lex.l

####################################################################################################
clean:
	rm -f *.o y.tab.h y.tab.c lex.yy.c main interface


	# ---------------------------------------------------------------------------- #

#	all: y.tab.c lex.yy.c main interface

#	y.tab.c: syntax.y
#		yacc -d syntax.y

#	lex.yy.c: lex.l
#		flex lex.l

	#FLAGS := -std=c99 -Wall -Wextra -pedantic-errors -O2 -g
#	FLAGS := -g
#	FLAGS += $(shell pkg-config --cflags --libs glib-2.0 gtk+-3.0)
#	GLIB_FLAGS= `pkg-config --cflags glib-2.0`

	  # ----------------------------- #
#	interface:
#		$(CC) $(SRCS) $(GLIB_FLAGS) $(FLAGS) -o interface

#	SRCS   := $(shell find . -name '*.c' ! -name 'interface.c')

#	.PHONY: main
#	$(TARGET):
#		$(CC) $(SRCS) $(GLIB_FLAGS) $(FLAGS) -o $@

	#.PHONY: clean
	#clean:
	#	rm -f $(TARGET)

#	clean:
#		rm -f *.o y.tab.h y.tab.c lex.yy.c main interface

	# ---------------------------------------------------------------------------- #
