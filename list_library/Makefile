
test: lista.o test.o
	gcc -o test test.o lista.o

lista.o:lista.c lista.h
	gcc -c lista.c
	
	
test.o:test.c lista.h
	gcc -c test.c
	
clean:
	rm lista.o test.o test
