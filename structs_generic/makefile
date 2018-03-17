CC=gcc
CFLAGS=-Wall

teste: teste.c nodes.o darray.o 
	$(CC) $(CFLAGS) -o teste teste.c darray.o nodes.o

darray.o: darray.c nodes.o 
	$(CC) $(CFLAGS) -c darray.c

nodes.o: nodes.c
	$(CC) $(CFLAGS) -c nodes.c

clean:
	rm -f *.o
