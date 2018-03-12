CC= gcc
CFLAGS= -Wextra -Wall  
LINGUAGEM= linguagem
LIBS= `pkg-config --cflags glib-2.0`
ALIBS= `pkg-config --libs glib-2.0`
NOME_LINGUAGEM= mycc


######################################################################

$(LINGUAGEM): y.tab.o lex.yy.o struct.o attribution.o
	$(CC) $(CFLAGS) $(ALIBS) -o $(LINGUAGEM) y.tab.o lex.yy.o struct.o attribution.o
	
######################################################################

install: $(LINGUAGEM) clean
	chmod +x install.sh
	./install.sh $(LINGUAGEM) $(NOME_LINGUAGEM)

######################################################################

uninstall: 
	rm -i ~/bin/$(NOME_LINGUAGEM)

######################################################################

y.tab.o: y.tab.c 
	$(CC) $(CFLAGS) $(LIBS) -c y.tab.c

y.tab.c: $(LINGUAGEM).y
	yacc -d --verbose $(LINGUAGEM).y

######################################################################

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) $(LIBS) -c lex.yy.c

lex.yy.c: $(LINGUAGEM).l y.tab.h
	flex -l $(LINGUAGEM).l 

######################################################################

struct.o: struct.c
	$(CC) $(CFLAGS) $(LIBS) -c struct.c

######################################################################

attribution.o: attribution.c
	$(CC) $(CFLAGS) $(LIBS) -c attribution.c

######################################################################

clean:
	rm -f lex.yy.c y.output y.tab.c y.tab.h *.o 
