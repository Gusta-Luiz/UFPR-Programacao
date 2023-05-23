all: poema

poema: poema.o
	gcc -o poema poema.o

poema.o: poema.c
	gcc -c poema.c -Wall

clean:
	rm -f *.o poema